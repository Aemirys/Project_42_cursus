<?php
session_start();
require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';

$errors = [];
$success = false;

$token = $_GET['token'] ?? '';
$email = $_GET['email'] ?? '';

if (!$token || !$email) {
    http_response_code(400);
    $errors[] = "Lien invalide.";
} else {
    $email = filter_var($email, FILTER_VALIDATE_EMAIL) ?: '';
    if (!$email) {
        http_response_code(400);
        $errors[] = "Lien invalide.";
    }
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && empty($errors)) {
    if (!verify_csrf($_POST['csrf'] ?? '')) {
        $errors[] = "Token CSRF invalide.";
    } else {
        $password = $_POST['password'] ?? '';
        $confirm  = $_POST['confirm'] ?? '';

        if (strlen($password) < 8 || $password !== $confirm) {
            $errors[] = "Mot de passe ≥ 8 caractères et confirmation identique.";
        } else {
            $pdo = get_db();
            $stmt = $pdo->prepare('SELECT id FROM users WHERE email=? AND reset_token=?');
            $stmt->execute([$email, $token]);
            $user = $stmt->fetch();

            if (!$user) {
                $errors[] = "Lien invalide ou expiré.";
            } else {
                $hash = password_hash($password, PASSWORD_DEFAULT);
                $stmt = $pdo->prepare('UPDATE users SET password_hash=?, reset_token=NULL WHERE id=?');
                $stmt->execute([$hash, $user['id']]);
                $success = true;
            }
        }
    }
}

include '../src/views/header.php';
?>

<h1>Réinitialisation du mot de passe</h1>

<?php foreach ($errors as $err): ?>
  <p class="error"><?= htmlspecialchars($err) ?></p>
<?php endforeach; ?>

<?php if ($success): ?>
  <p class="success">
    Mot de passe modifié avec succès !
    <a href="/login.php">Se connecter</a>
  </p>
<?php else: ?>
  <form method="POST">
    <input type="hidden" name="csrf" value="<?= csrf_token() ?>">

    <label for="password">Nouveau mot de passe</label>
    <input id="password" type="password" name="password" required>

    <label for="confirm">Confirmer le mot de passe</label>
    <input id="confirm" type="password" name="confirm" required>

    <button type="submit">Réinitialiser</button>
  </form>
<?php endif; ?>

<?php include '../src/views/footer.php'; ?>

