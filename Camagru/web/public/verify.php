<?php
require_once '../src/utils/db.php';

$pdo = get_db();

$token = $_GET['token'] ?? null;
$email = $_GET['email'] ?? null;

if ($token && $email) {
    $stmt = $pdo->prepare(
        "SELECT id FROM users WHERE email = ? AND confirm_token = ?"
    );
    $stmt->execute([$email, $token]);
    $user = $stmt->fetch();

    if ($user) {
        $upd = $pdo->prepare(
            "UPDATE users
             SET is_confirmed = 1,
                 confirm_token = NULL
             WHERE id = ?"
        );
        $upd->execute([$user['id']]);
    }
}

header('Location: /login.php?confirmed=1');
exit;
