<?php
session_start();

require_once dirname(__DIR__) . '/src/utils/filesystem.php';
ensure_directories();

require_once '../src/utils/db.php';
require_once '../src/utils/auth.php';
require_once '../src/utils/csrf.php';
require_once '../src/utils/avatar.php';

require_login();

$pdo = get_db();
$errors = [];
$success = false;

// Charger données utilisateur
$stmt = $pdo->prepare("
    SELECT username, email, notify_on_comment, created_at, avatar_path
    FROM users WHERE id=?
");
$stmt->execute([$_SESSION["user_id"]]);
$user = $stmt->fetch();

/* =========================
   UPDATE PROFIL
========================= */
if ($_SERVER["REQUEST_METHOD"] === "POST" && ($_POST["form"] ?? "") === "profile") {

    if (!verify_csrf($_POST["csrf"] ?? "")) {
        $errors[] = "Token CSRF invalide.";
    } else {
        $new_username = trim($_POST["username"]);
        $new_email = filter_var($_POST["email"], FILTER_VALIDATE_EMAIL);
        $notify = isset($_POST["notify_on_comment"]) ? 1 : 0;

        if (!$new_email || strlen($new_username) < 3) {
            $errors[] = "Champs invalides.";
        } else {
            $check = $pdo->prepare("
                SELECT id FROM users
                WHERE (username=? OR email=?) AND id!=?
            ");
            $check->execute([$new_username, $new_email, $_SESSION["user_id"]]);

            if ($check->fetch()) {
                $errors[] = "Nom ou email déjà utilisé.";
            } else {
                $upd = $pdo->prepare("
                    UPDATE users
                    SET username=?, email=?, notify_on_comment=?
                    WHERE id=?
                ");
                $upd->execute([$new_username, $new_email, $notify, $_SESSION["user_id"]]);

                $_SESSION["username"] = $new_username;
                $user["username"] = $new_username;
                $user["email"] = $new_email;
                $user["notify_on_comment"] = $notify;
                $success = true;
            }
        }
    }
}

/* =========================
   UPLOAD AVATAR
========================= */
if ($_SERVER["REQUEST_METHOD"] === "POST" && ($_POST["form"] ?? "") === "avatar") {

    if (!verify_csrf($_POST["csrf"] ?? "")) {
        $errors[] = "Token CSRF invalide.";
    } else {

        // Revenir à l’avatar par défaut
        if (isset($_POST['reset_avatar'])) {
            $upd = $pdo->prepare("UPDATE users SET avatar_path='default_avatar.png' WHERE id=?");
            $upd->execute([$_SESSION["user_id"]]);
            $user['avatar_path'] = 'default_avatar.png';
            $success = true;

        } else {
            $filename = handle_avatar_upload($_SESSION["user_id"]);

            if ($filename) {
                $upd = $pdo->prepare("UPDATE users SET avatar_path=? WHERE id=?");
                $upd->execute([$filename, $_SESSION["user_id"]]);
                $user["avatar_path"] = $filename;
                $success = true;
            } else {
                $errors[] = "Erreur lors de l'upload (JPG/PNG)";
            }
        }
    }
}

/* =========================
   AVATAR SOURCE
========================= */
if ($user['avatar_path'] === 'default_avatar.png' || empty($user['avatar_path'])) {
    $avatarSrc = '/assets/default_avatar.png';
} else {
    $path = __DIR__ . '/avatar/' . $user['avatar_path'];
    $avatarSrc = is_file($path)
        ? '/avatar/' . htmlspecialchars($user['avatar_path'])
        : '/assets/default_avatar.png';
}

include '../src/views/header.php';
?>

<a href="/index.php" class="back-btn">← Retour</a>

<h1 class="title-pixar">Mon Profil 🎈</h1>

<div class="profile-container">

    <?php foreach ($errors as $e): ?>
        <p class="error"><?= htmlspecialchars($e) ?></p>
    <?php endforeach; ?>

    <?php if ($success): ?>
        <p class="success">Profil mis à jour ! 🎉</p>
    <?php endif; ?>

    <!-- ================= AVATAR ================= -->
    <div class="avatar-section">

        <img id="avatar-preview"
             src="<?= $avatarSrc ?>"
             class="avatar-preview"
             alt="Avatar">

        <form method="POST" enctype="multipart/form-data">
            <input type="hidden" name="csrf" value="<?= csrf_token() ?>">
            <input type="hidden" name="form" value="avatar">

            <input type="file"
                   name="avatar"
                   id="avatar-input"
                   accept="image/jpeg,image/png">

            <div style="margin-top:15px;">
                <button type="submit">Changer l’avatar 🎈</button>
                <button style="margin-top:15px;" type="button" id="cancel-avatar">Annuler</button>
            </div>

            <div style="margin-top:10px;">
                <button type="submit"
                        name="reset_avatar"
                        value="1">
                    Revenir à l’avatar par défaut
                </button>
            </div>
        </form>
    </div>

    <!-- ================= PROFIL ================= -->
    <section class="profile-section">
        <h2>Informations personnelles</h2>

        <form method="POST">
            <input type="hidden" name="csrf" value="<?= csrf_token() ?>">
            <input type="hidden" name="form" value="profile">

            <label>Nom d'utilisateur</label>
            <input type="text" name="username" class="input-large" value="<?= htmlspecialchars($user["username"]) ?>">

            <label>Email</label>
            <input type="email" name="email" class="input-large" value="<?= htmlspecialchars($user["email"]) ?>">

            <label class="checkbox-label">
                <input type="checkbox" name="notify_on_comment"
                    <?= $user["notify_on_comment"] ? "checked" : "" ?>>
                <span>Recevoir un email lors d’un commentaire</span>
            </label>
            <button type="submit">Mettre à jour</button>
        </form>
        <div style="margin-top:20px; text-align:center;">
            <form action="/change_password.php" method="GET">
                <button type="submit">🔒 Changer le mot de passe</button>
            </form>
        </div>
        
        <div style="margin-top:30px; text-align:center;">
            <form action="/delete_account.php" method="GET">
                <p style="margin-bottom:15px;">
                   ⚠️ La suppression de votre compte est définitive.
                </p>
                <button type="submit" class="danger">
                    🗑️ Supprimer mon compte
                </button>
            </form>
        </div>

    </section>

</div>

<!-- ================= JS PREVIEW ================= -->
<script>
const input = document.getElementById('avatar-input');
const preview = document.getElementById('avatar-preview');
const cancelBtn = document.getElementById('cancel-avatar');

const originalSrc = preview.src;

input.addEventListener('change', () => {
    const file = input.files[0];
    if (!file) return;

    if (!file.type.match(/^image\/(jpeg|png)$/)) {
        alert('Format invalide (JPG/PNG)');
        input.value = '';
        return;
    }

    const reader = new FileReader();
    reader.onload = e => preview.src = e.target.result;
    reader.readAsDataURL(file);
});

cancelBtn.addEventListener('click', () => {
    preview.src = originalSrc;
    input.value = '';
});
</script>

<?php include '../src/views/footer.php'; ?>
