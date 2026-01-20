<?php
session_start();
require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';
require_once '../src/utils/mail.php';

$errors = [];
$success = false;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!verify_csrf($_POST['csrf'] ?? '')) {
        $errors[] = "Token CSRF invalide.";
    } else {
        $email = filter_var($_POST['email'] ?? '', FILTER_VALIDATE_EMAIL);

        if (!$email) {
            $errors[] = "Email invalide.";
        } else {
            $pdo = get_db();
            $stmt = $pdo->prepare('SELECT id, username FROM users WHERE email=?');
            $stmt->execute([$email]);
            $user = $stmt->fetch();

            if (!$user) {
                $errors[] = "Aucun compte associé à cet email.";
            } else {
                $token = bin2hex(random_bytes(32));
                $stmt = $pdo->prepare('UPDATE users SET reset_token=? WHERE id=?');
                $stmt->execute([$token, $user['id']]);

                $host = $_SERVER['HTTP_HOST'];
                $link = "https://$host/reset_password.php?token=$token&email=" . urlencode($email);

                $subject = "Réinitialisation de votre mot de passe Camagru";
                $body = "Salut {$user['username']},\n\n";
                $body .= "Clique sur ce lien pour réinitialiser ton mot de passe :\n$link\n\n";
                $body .= "Si tu n'es pas à l'origine de cette demande, ignore ce mail.";

                send_mail($email, $subject, $body);
                $success = true;
            }
        }
    }
}

include '../src/views/header.php';
?>

<h1>Mot de passe oublié 🎈</h1>

<?php if ($success): ?>
    <p class="success">
        Un email de réinitialisation a été envoyé.<br>
        Vérifie ta boîte de réception ✉️
    </p>
<?php else: ?>

    <?php foreach ($errors as $err): ?>
        <p class="error"><?= htmlspecialchars($err) ?></p>
    <?php endforeach; ?>

    <form method="POST">
        <input type="hidden" name="csrf" value="<?= csrf_token() ?>">

        <label for="email">Adresse email</label>
        <input
            type="email"
            id="email"
            name="email"
            placeholder="ex: woody@pixar.com"
            required
        >

        <button type="submit">Envoyer le lien ✨</button>
    </form>

<?php endif; ?>

<p style="text-align:center; margin-top:15px;">
    <a href="/login.php">← Retour à la connexion</a>
</p>

<?php include '../src/views/footer.php'; ?>
