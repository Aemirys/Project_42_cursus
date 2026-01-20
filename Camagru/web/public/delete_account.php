<?php
session_start();

require_once '../src/utils/db.php';
require_once '../src/utils/auth.php';
require_once '../src/utils/csrf.php';

require_login();

$pdo = get_db();
$errors = [];
$success = false;

// Récupère hash mdp user
$stmt = $pdo->prepare("SELECT password_hash FROM users WHERE id=?");
$stmt->execute([$_SESSION['user_id']]);
$user = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$user) {
    header("Location: logout.php");
    exit;
}

$userId = (int)$_SESSION['user_id'];


$uploadsDir = realpath(__DIR__ . '/uploads');
$thumbsDir  = realpath(__DIR__ . '/thumbs');

if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    if (!verify_csrf($_POST['csrf'] ?? '')) {
        $errors[] = "Token CSRF invalide.";
    } else {
        $password = $_POST['password'] ?? '';

        if (!password_verify($password, $user['password_hash'])) {
            $errors[] = "Mot de passe incorrect.";
        } else {
            try {
                $stmt = $pdo->prepare("SELECT id, filename, thumb FROM images WHERE user_id=?");
                $stmt->execute([$userId]);
                $images = $stmt->fetchAll(PDO::FETCH_ASSOC);

                $imageIds = array_map(fn($r) => (int)$r['id'], $images);

                $pdo->beginTransaction();

                if (!empty($imageIds)) {
                    $in = implode(',', array_fill(0, count($imageIds), '?'));

                    $stmt = $pdo->prepare("DELETE FROM likes WHERE image_id IN ($in)");
                    $stmt->execute($imageIds);

                    $stmt = $pdo->prepare("DELETE FROM comments WHERE image_id IN ($in)");
                    $stmt->execute($imageIds);
                }

                $stmt = $pdo->prepare("DELETE FROM likes WHERE user_id=?");
                $stmt->execute([$userId]);

                $stmt = $pdo->prepare("DELETE FROM comments WHERE user_id=?");
                $stmt->execute([$userId]);

                $stmt = $pdo->prepare("DELETE FROM images WHERE user_id=?");
                $stmt->execute([$userId]);

                $stmt = $pdo->prepare("DELETE FROM users WHERE id=?");
                $stmt->execute([$userId]);

                $pdo->commit();

                foreach ($images as $img) {
                    $filename = $img['filename'] ?? '';
                    $thumb    = $img['thumb'] ?? '';

                    if ($uploadsDir && $filename) {
                        $p = realpath($uploadsDir . DIRECTORY_SEPARATOR . $filename);
                        if ($p && str_starts_with($p, $uploadsDir) && is_file($p)) {
                            @unlink($p);
                        }
                    }

                    if ($thumbsDir && $thumb) {
                        $p = realpath($thumbsDir . DIRECTORY_SEPARATOR . $thumb);
                        if ($p && str_starts_with($p, $thumbsDir) && is_file($p)) {
                            @unlink($p);
                        }
                    }
                }

                session_destroy();
                $success = true;

            } catch (Throwable $e) {
                if ($pdo->inTransaction()) $pdo->rollBack();
                $errors[] = "Erreur lors de la suppression du compte.";
            }
        }
    }
}

include '../src/views/header.php';
?>

<div class="profile-container">

    <h1>Supprimer mon compte</h1>

    <?php if ($success): ?>
        <p class="success">Votre compte a été supprimé.</p>
        <p><a href="index.php">Retour à l'accueil</a></p>
        <?php include '../src/views/footer.php'; exit; ?>
    <?php endif; ?>

    <?php foreach ($errors as $err): ?>
        <p class="error"><?= htmlspecialchars($err) ?></p>
    <?php endforeach; ?>

    <p class="warning">
        ⚠ Cette action est <strong>définitive</strong>. Toutes vos photos, commentaires et likes seront supprimés.
    </p>

    <form method="POST" class="profile-form">
        <input type="hidden" name="csrf" value="<?= htmlspecialchars(csrf_token()) ?>">

        <label>Entrez votre mot de passe pour confirmer</label>
        <input type="password" name="password" required>

        <button type="submit" class="danger">Supprimer définitivement mon compte</button>
        <button  style="margin-top:30px; text-align:center;" type="button" onclick="window.location.href='/profile.php'">
            Annuler
        </button>
    </form>
</div>

<?php include '../src/views/footer.php'; ?>
