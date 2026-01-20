<?php
$page = 'gallery';
session_start();
require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';
include '../src/views/header.php';

$pdo = get_db();

$per_page = 12;
$pageNum = max(1, (int)($_GET['p'] ?? 1));
$offset = ($pageNum - 1) * $per_page;

$total = (int)$pdo->query("SELECT COUNT(*) FROM images")->fetchColumn();
$total_pages = max(1, (int)ceil($total / $per_page));

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

$image_ids = array_map(fn($i) => (int)$i['id'], $images);

/* Likes utilisateur */
$user_likes = [];
if (isset($_SESSION['user_id']) && $image_ids) {
    $in = implode(',', array_fill(0, count($image_ids), '?'));
    $params = array_merge([$_SESSION['user_id']], $image_ids);

    $stmt = $pdo->prepare("
        SELECT image_id FROM likes
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
?>

<h1>Galerie 📸</h1>

<div class="gallery">

<?php foreach ($images as $img): ?>
<?php $id = (int)$img['id']; ?>
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
        <?php $commentCount = count($comments_by_image[$id] ?? []); ?>

        <?php if ($commentCount > 0 || $is_logged_in): ?>
            <button class="ig-comment-toggle" data-id="<?= $id ?>">💬</button>
        <?php else: ?>
            <span class="ig-comment-disabled" title="Aucun commentaire">💬</span>
        <?php endif; ?>

        <!-- DELETE -->
        <?php if ($is_logged_in && (int)$_SESSION['user_id'] === (int)$img['user_id']): ?>
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

</div>

<!-- INFINITE SCROLL sentinel -->
<div id="infinite-sentinel" style="height:1px;"></div>
<div id="infinite-loading" style="display:none; text-align:center; padding:16px;">
    Chargement…
</div>

<!-- ZOOM MODAL -->
<div class="ig-zoom-modal" id="zoomModal">
    <button class="ig-zoom-close" aria-label="Fermer">✕</button>
    <img src="" alt="">
</div>

<script>
const IS_LOGGED_IN = <?= $is_logged_in ? 'true' : 'false' ?>;
const CSRF_TOKEN = <?= json_encode($csrf) ?>;

let currentPage = <?= (int)$pageNum ?>;
const TOTAL_PAGES = <?= (int)$total_pages ?>;

const gallery = document.querySelector('.gallery');
const sentinel = document.getElementById('infinite-sentinel');
const loading = document.getElementById('infinite-loading');

let isLoading = false;

/* LIKE AJAX  */
document.addEventListener('click', e => {
  if (!e.target.classList.contains('ig-like-btn')) return;

  if (!IS_LOGGED_IN) {
    window.location.href = '/login.php';
    return;
  }

  const btn = e.target;
  const id = btn.dataset.id;

  fetch('/toggle_like.php', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'X-CSRF-Token': CSRF_TOKEN
    },
    body: JSON.stringify({ image_id: id })
  })
  .then(async r => {
    if (!r.ok) {
      if (r.status === 401) window.location.href = '/login.php';
      throw new Error('HTTP ' + r.status);
    }
    return r.json();
  })
  .then(data => {
    if (!data || data.success !== true) return;
    btn.textContent = data.liked ? '❤️' : '🤍';
    const el = document.getElementById('likes-' + id);
    if (el) el.textContent = data.like_count;
  })
  .catch(err => {
    console.error('Erreur like:', err);
  });
});

/* TOGGLE COMMENTS */
document.addEventListener('click', e => {
  if (!e.target.classList.contains('ig-comment-toggle')) return;

  const id = e.target.dataset.id;
  const wrap = document.getElementById('comments-' + id);
  if (!wrap) return;

  const hasComment = wrap.querySelector('p');
  const hasForm = wrap.querySelector('form');
  if (!hasComment && !hasForm) return;

  wrap.classList.toggle('open');
});

/* ADD COMMENT */
document.addEventListener('submit', async (e) => {
  const form = e.target;
  if (!form.classList.contains('ig-comment-form')) return;

  e.preventDefault();

  if (!IS_LOGGED_IN) {
    window.location.href = '/login.php';
    return;
  }

  const fd = new FormData(form);

  const res = await fetch('/add_comment.php', {
    method: 'POST',
    headers: {
      'X-Requested-With': 'XMLHttpRequest',
      'Accept': 'application/json'
    },
    body: fd
  });

  if (res.status === 401) {
    window.location.href = '/login.php';
    return;
  }

  if (!res.ok) return;

  const data = await res.json();
  if (!data || data.success !== true) return;

  const imageId = data.comment.image_id;
  const wrap = document.getElementById('comments-' + imageId);
  if (!wrap) return;

  const p = document.createElement('p');
  p.innerHTML = `<strong>${escapeHtml(data.comment.username)}</strong> ${escapeHtml(data.comment.content).replace(/\n/g, '<br>')}`;

  const existingForm = wrap.querySelector('form');
  wrap.insertBefore(p, existingForm);

  const ta = form.querySelector('textarea[name="content"]');
  if (ta) ta.value = '';

  wrap.classList.remove('open');

  const cc = document.getElementById('comment-count-' + imageId);
  if (cc) cc.textContent = String(parseInt(cc.textContent || '0', 10) + 1);
});

function escapeHtml(str) {
  return String(str)
    .replaceAll('&', '&amp;')
    .replaceAll('<', '&lt;')
    .replaceAll('>', '&gt;')
    .replaceAll('"', '&quot;')
    .replaceAll("'", '&#039;');
}

/* IMAGE ZOOM */
const zoomModal = document.getElementById('zoomModal');
const zoomImg = zoomModal.querySelector('img');
const zoomClose = zoomModal.querySelector('.ig-zoom-close');

function bindZoomOnNewImages() {
  document.querySelectorAll('.ig-image').forEach(img => {
    if (img.dataset.boundZoom) return;
    img.dataset.boundZoom = "1";
    img.addEventListener('click', () => {
      zoomImg.src = img.dataset.full;
      zoomModal.classList.add('open');
    });
  });
}
bindZoomOnNewImages();

zoomClose.addEventListener('click', () => {
  zoomModal.classList.remove('open');
});
zoomModal.addEventListener('click', e => {
  if (e.target === zoomModal) zoomModal.classList.remove('open');
});

/* INFINITE SCROLL */
async function loadNextPage() {

  if (isLoading) return;
  if (currentPage >= TOTAL_PAGES) return;

  isLoading = true;
  loading.style.display = 'block';

  const next = currentPage + 1;
  
  try {
    const res = await fetch('/gallery_page.php?p=' + next, {
      headers: { 'X-Requested-With': 'XMLHttpRequest' }
    });

    const html = await res.text();

    if (res.ok && html.trim().length > 0) {
      gallery.insertAdjacentHTML('beforeend', html);
      currentPage = next;
      bindZoomOnNewImages();
      io.unobserve(sentinel);
      io.observe(sentinel);

    } else {
      currentPage = TOTAL_PAGES;
    }
  } catch (e) {
    console.log('Fetch error', e);
  }

  loading.style.display = 'none';
  isLoading = false;
}


let io = new IntersectionObserver(entries => {
  if (entries.some(e => e.isIntersecting)) loadNextPage();
}, { rootMargin: '600px' });

io.observe(sentinel);

document.addEventListener('click', (e) => {

  if (e.target.classList.contains('ig-comment-toggle')) return;
  const insideComments = e.target.closest('.ig-comments-wrap');
  if (insideComments) return;

  document.querySelectorAll('.ig-comments-wrap.open').forEach(w => {
    w.classList.remove('open');
  });
});

</script>

<?php include '../src/views/footer.php'; ?>
