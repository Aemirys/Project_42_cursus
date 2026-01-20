<?php
session_start();

require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';

$pdo = get_db();

$per_page = 12;
$pageNum = max(1, (int)($_GET['p'] ?? 1));
$offset = ($pageNum - 1) * $per_page;

/* Images + likes */
$stmt = $pdo->prepare("
    SELECT images.*, users.username, COUNT(likes.id) AS like_count
    FROM images
    JOIN users ON images.user_id = users.id
    LEFT JOIN likes ON likes.image_id = images.id
    GROUP BY images.id
    ORDER BY images.created_at DESC
    LIMIT :limit OFFSET :offset
");
$stmt->bindValue(':limit', $per_page, PDO::PARAM_INT);
$stmt->bindValue(':offset', $offset, PDO::PARAM_INT);
$stmt->execute();
$images = $stmt->fetchAll(PDO::FETCH_ASSOC);

if (!$images) {
    exit;
}

$image_ids = array_map(fn($i) => (int)$i['id'], $images);

/* Likes utilisateur */
$user_likes = [];
if (isset($_SESSION['user_id']) && $image_ids) {
    $in = implode(',', array_fill(0, count($image_ids), '?'));
    $params = array_merge([$_SESSION['user_id']], $image_ids);

    $stmt = $pdo->prepare("
        SELECT image_id
        FROM likes
        WHERE user_id = ? AND image_id IN ($in)
    ");
    $stmt->execute($params);
    $user_likes = $stmt->fetchAll(PDO::FETCH_COLUMN);
}

/* Commentaires */
$comments_by_image = [];
if ($image_ids) {
    $in = implode(',', array_fill(0, count($image_ids), '?'));
    $stmt = $pdo->prepare("
        SELECT comments.image_id, comments.content, users.username
        FROM comments
        JOIN users ON comments.user_id = users.id
        WHERE comments.image_id IN ($in)
        ORDER BY comments.created_at ASC
    ");
    $stmt->execute($image_ids);

    foreach ($stmt->fetchAll(PDO::FETCH_ASSOC) as $c) {
        $comments_by_image[(int)$c['image_id']][] = $c;
    }
}

$is_logged_in = isset($_SESSION['user_id']);
$csrf = csrf_token();


foreach ($images as $img):
    $id = (int)$img['id'];
    $commentCount = count($comments_by_image[$id] ?? []);
?>
<div class="ig-card">

    <!-- IMAGE -->
    <img class="ig-image"
         src="/uploads/<?= htmlspecialchars($img['filename']) ?>"
         alt="photo"
         data-full="/uploads/<?= htmlspecialchars($img['filename']) ?>">

    <!-- AUTHOR -->
    <div class="ig-author">
        <strong>@<?= htmlspecialchars($img['username']) ?></strong>
        <?php if (!empty($img['created_at'])): ?>
            <span class="ig-date">
                <?= htmlspecialchars((new DateTime($img['created_at']))->format('d/m/Y H:i')) ?>
            </span>
        <?php endif; ?>
    </div>

    <!-- ACTIONS -->
    <div class="ig-actions">

        <!-- LIKE -->
        <button class="ig-like-btn"
                data-id="<?= $id ?>"
                <?= $is_logged_in ? '' : 'disabled' ?>>
            <?= in_array($id, $user_likes) ? '❤️' : '🤍' ?>
        </button>

        <!-- COMMENT (toggle) -->
        <?php if ($commentCount > 0 || $is_logged_in): ?>
            <button class="ig-comment-toggle" data-id="<?= $id ?>">💬</button>
        <?php else: ?>
            <span class="ig-comment-disabled" title="Aucun commentaire">💬</span>
        <?php endif; ?>

        <!-- DELETE -->
        <?php if (
            $is_logged_in &&
            (int)$_SESSION['user_id'] === (int)$img['user_id']
        ): ?>
            <form method="POST"
                  action="delete_image.php"
                  class="ig-delete-form"
                  onsubmit="return confirm('Supprimer cette image ?');">
                <input type="hidden" name="csrf" value="<?= htmlspecialchars($csrf) ?>">
                <input type="hidden" name="image_id" value="<?= $id ?>">
                <button type="submit" class="ig-delete-btn">🗑</button>
            </form>
        <?php endif; ?>

    </div>

    <!-- COUNTERS -->
    <div class="ig-counters">
        <span id="likes-<?= $id ?>"><?= (int)$img['like_count'] ?></span>

        <span class="comment-count" id="comment-count-<?= $id ?>">
            <?= $commentCount ?>
        </span>
    </div>

    <!-- COMMENTS -->
    <div class="ig-comments-wrap" id="comments-<?= $id ?>">

        <?php foreach (($comments_by_image[$id] ?? []) as $c): ?>
            <p>
                <strong><?= htmlspecialchars($c['username']) ?></strong>
                <?= nl2br(htmlspecialchars($c['content'])) ?>
            </p>
        <?php endforeach; ?>

        <?php if ($is_logged_in): ?>
            <form method="POST" action="add_comment.php" class="ig-comment-form">
                <input type="hidden" name="csrf" value="<?= htmlspecialchars($csrf) ?>">
                <input type="hidden" name="image_id" value="<?= $id ?>">
                <textarea name="content"
                          placeholder="Ajouter un commentaire…"
                          required maxlength="500"
                          rows="2"></textarea>

                <button type="submit">Publier</button>
            </form>
        <?php endif; ?>

    </div>

</div>
<?php endforeach; ?>
