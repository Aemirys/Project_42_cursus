<?php
session_start();
require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';

$errors = [];

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (!verify_csrf($_POST['csrf'] ?? '')) {
        $errors[] = "Token CSRF invalide.";
    } else {
        $username = trim($_POST["username"]);
        $password = $_POST["password"];

        $pdo = get_db();
        $stmt = $pdo->prepare("SELECT id, password_hash, is_confirmed FROM users WHERE username=?");
        $stmt->execute([$username]);
        $user = $stmt->fetch();

        if (!$user || !password_verify($password, $user['password_hash'])) {
            $errors[] = "Identifiants incorrects.";
        } elseif (!$user["is_confirmed"]) {
            $errors[] = "Veuillez d'abord confirmer votre email.";
        } else {
            session_regenerate_id(true);
            $_SESSION["user_id"] = $user["id"];
            $_SESSION["username"] = $username;
            header("Location: /index.php");
            exit;
        }
    }
}

include '../src/views/header.php';
?>

<h1 class="title-pixar">Connexion 🎈</h1>

<?php if (isset($_GET['confirmed'])): ?>
    <p class="success">🎉 Compte confirmé ! Vous pouvez vous connecter.</p>
<?php endif; ?>

<?php foreach ($errors as $e): ?>
    <p class="error"><?= htmlspecialchars($e) ?></p>
<?php endforeach; ?>

<form method="POST">
    <input type="hidden" name="csrf" value="<?= csrf_token() ?>">

    <label>Nom d'utilisateur</label>
    <input type="text" name="username" required>

    <label>Mot de passe</label>
    <input type="password" name="password" required>

    <button type="submit">Se connecter ✨</button>

    <a href="/reset_request.php">Mot de passe oublié ?</a>
</form>

<?php include '../src/views/footer.php'; ?>
