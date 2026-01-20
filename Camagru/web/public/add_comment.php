<?php
session_start();
require_once '../src/utils/db.php';
require_once '../src/utils/mail.php';
require_once '../src/utils/csrf.php';

function is_ajax_request(): bool {
    return (isset($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) === 'xmlhttprequest')
        || (isset($_SERVER['HTTP_ACCEPT']) && str_contains($_SERVER['HTTP_ACCEPT'], 'application/json'));
}

function json_response(array $data, int $status = 200): void {
    http_response_code($status);
    header('Content-Type: application/json; charset=utf-8');
    echo json_encode($data);
    exit;
}

$ajax = is_ajax_request();

if (!isset($_SESSION['user_id'])) {
    if ($ajax) json_response(['success' => false, 'error' => 'not_logged_in'], 401);
    header('Location: /login.php');
    exit;
}

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    if ($ajax) json_response(['success' => false, 'error' => 'method_not_allowed'], 405);
    http_response_code(405);
    exit('Méthode invalide');
}

if (!verify_csrf($_POST['csrf'] ?? '')) {
    if ($ajax) json_response(['success' => false, 'error' => 'bad_csrf'], 403);
    http_response_code(403);
    exit('Token CSRF invalide');
}

$user_id  = (int)$_SESSION['user_id'];
$image_id = (int)($_POST['image_id'] ?? 0);
$content  = trim($_POST['content'] ?? '');

if ($image_id <= 0 || $content === '') {
    if ($ajax) json_response(['success' => false, 'error' => 'invalid_input'], 422);
    header('Location: /gallery.php');
    exit;
}

if (mb_strlen($content) > 500) {
    $content = mb_substr($content, 0, 500);
}

$pdo = get_db();

$stmt = $pdo->prepare("
    SELECT images.user_id AS owner_id, users.email, users.username, users.notify_on_comment
    FROM images
    JOIN users ON images.user_id = users.id
    WHERE images.id = ?
");
$stmt->execute([$image_id]);
$img = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$img) {
    if ($ajax) json_response(['success' => false, 'error' => 'image_not_found'], 404);
    header('Location: /gallery.php');
    exit;
}

$stmt = $pdo->prepare("INSERT INTO comments (user_id, image_id, content) VALUES (?, ?, ?)");
$stmt->execute([$user_id, $image_id, $content]);


$stmt = $pdo->prepare("SELECT username FROM users WHERE id = ?");
$stmt->execute([$user_id]);
$comment_author = (string)$stmt->fetchColumn();

if ((int)$img['notify_on_comment'] === 1 && (int)$img['owner_id'] !== $user_id) {
    $body = "Salut {$img['username']} 👋\n\nQuelqu'un a commenté ta photo :\n\n{$content}\n\n— Camagru";
    send_mail($img['email'], 'Nouveau commentaire sur ta photo (Camagru)', $body);
}

if ($ajax) {
    json_response([
        'success' => true,
        'comment' => [
            'image_id' => $image_id,
            'username' => $comment_author,
            'content'  => $content
        ]
    ]);
}

header('Location: /gallery.php');
exit;