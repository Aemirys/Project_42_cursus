<?php
session_start();
require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';
require_once '../src/utils/auth.php';

require_login();

$errors = [];
$success = false;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!verify_csrf($_POST['csrf'] ?? '')) {
        $errors[] = "Token CSRF invalide.";
    } else {
        $current = $_POST['current_password'] ?? '';
        $new = $_POST['new_password'] ?? '';
        $confirm = $_POST['confirm_password'] ?? '';

        if (!$current || strlen($new) < 8) {
            $errors[] = "Remplissez tous les champs correctement (nouveau ≥ 8 caractères).";
        } elseif ($new !== $confirm) {
            $errors[] = "La confirmation du mot de passe ne correspond pas.";
        } else {
            $pdo = get_db();
            $stmt = $pdo->prepare('SELECT password_hash FROM users WHERE id=?');
            $stmt->execute([$_SESSION['user_id']]);
            $user = $stmt->fetch(PDO::FETCH_ASSOC);

            if (!$user || empty($user['password_hash'])) {
                $errors[] = "Utilisateur introuvable.";
            } elseif (!password_verify($current, $user['password_hash'])) {
                $errors[] = "Mot de passe actuel incorrect.";
            } else {
                $hash = password_hash($new, PASSWORD_DEFAULT);
                $stmt = $pdo->prepare('UPDATE users SET password_hash=? WHERE id=?');
                $stmt->execute([$hash, $_SESSION['user_id']]);
                $success = true;
            }
        }
    }
}

include '../src/views/header.php';
?>

<a href="/profile.php" class="back-btn">← Retour au profil</a>

<h1 class="title-pixar">Changer le mot de passe 🔒</h1>

<?php foreach ($errors as $err): ?>
  <p class="error"><?= htmlspecialchars($err) ?></p>
<?php endforeach; ?>

<?php if ($success): ?>
  <p class="success">Mot de passe mis à jour ! 🎉</p>
<?php endif; ?>

<form method="POST" class="form">
  <input type="hidden" name="csrf" value="<?= csrf_token() ?>">

  <label for="current_password">Mot de passe actuel</label>
  <input id="current_password" type="password" name="current_password" required>

  <label for="new_password">Nouveau mot de passe</label>
  <input id="new_password" type="password" name="new_password" required minlength="8">

  <label for="confirm_password">Confirmer le nouveau mot de passe</label>
  <input id="confirm_password" type="password" name="confirm_password" required minlength="8">

  <button type="submit">Modifier</button>
</form>

<?php include '../src/views/footer.php'; ?>
