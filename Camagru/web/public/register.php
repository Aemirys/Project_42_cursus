<?php
session_start();
require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';
require_once '../src/utils/mail.php';
require_once '../src/config/config.php';

$errors = [];
$success = false;

if ($_SERVER["REQUEST_METHOD"] === "POST") {

    if (!verify_csrf($_POST["csrf"] ?? "")) {
        $errors[] = "Token CSRF invalide.";
    } else {
        $username = trim($_POST["username"]);
        $email = filter_var($_POST["email"], FILTER_VALIDATE_EMAIL);
        $password = $_POST["password"];

        if (!$email || strlen($username) < 3 || strlen($password) < 8) {
            $errors[] = "Vérifiez les champs (username ≥ 3, mot de passe ≥ 8).";
        } else {
            $pdo = get_db();

            // Vérification des doublons
            $check = $pdo->prepare("SELECT id FROM users WHERE username=? OR email=?");
            $check->execute([$username, $email]);

            if ($check->fetch()) {
                $errors[] = "Nom d'utilisateur ou email déjà utilisé.";
            } else {
                $hash = password_hash($password, PASSWORD_DEFAULT);
                $token = bin2hex(random_bytes(32));

                $stmt = $pdo->prepare(
                    "INSERT INTO users (username, email, password_hash, confirm_token)
                     VALUES (?, ?, ?, ?)"
                );
                $stmt->execute([$username, $email, $hash, $token]);

                $link = APP_URL . '/verify.php'
                      . '?token=' . urlencode($token)
                      . '&email=' . urlencode($email);

                send_mail(
                    $email,
                    'Confirme ton compte Camagru 🎈',
                    "Salut $username !\nClique ici pour confirmer ton compte :\n$link"
                );

                $success = true;
            }
        }
    }
}

include '../src/views/header.php';
?>

<h1 class="title-pixar">Créer mon compte 🎈✨</h1>

<?php if ($success): ?>
    <p class="success">Inscription réussie ! Vérifiez vos emails.</p>
<?php else: ?>

    <?php foreach ($errors as $e): ?>
        <p class="error"><?= htmlspecialchars($e) ?></p>
    <?php endforeach; ?>

    <form method="POST">
        <input type="hidden" name="csrf" value="<?= csrf_token() ?>">

        <label>Nom d'utilisateur</label>
        <input type="text" name="username" required>

        <label>Email</label>
        <input type="email" name="email" required>

        <label>Mot de passe</label>
        <input type="password" name="password" required>

        <button type="submit">Créer mon compte ✨</button>

        <a href="/login.php">Déjà inscrit ?</a>
    </form>

<?php endif; ?>

<?php include '../src/views/footer.php'; ?>
