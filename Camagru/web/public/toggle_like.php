<?php
session_start();
require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';

header('Content-Type: application/json');

if (!isset($_SESSION['user_id'])) {
    http_response_code(401);
    echo json_encode(['success' => false, 'error' => 'not_authenticated']);
    exit;
}

// CSRF via header X-CSRF-Token (AJAX)
$csrf = $_SERVER['HTTP_X_CSRF_TOKEN'] ?? '';
if (!verify_csrf($csrf)) {
    http_response_code(403);
    echo json_encode(['success' => false, 'error' => 'csrf_invalid']);
    exit;
}

$data = json_decode(file_get_contents('php://input'), true);
$image_id = (int)($data['image_id'] ?? 0);
$user_id  = (int)$_SESSION['user_id'];

if ($image_id <= 0) {
    http_response_code(400);
    echo json_encode(['success' => false, 'error' => 'invalid_image_id']);
    exit;
}

$pdo = get_db();

// Vérifie que l'image existe
$chk = $pdo->prepare("SELECT id FROM images WHERE id=?");
$chk->execute([$image_id]);
if (!$chk->fetchColumn()) {
    http_response_code(404);
    echo json_encode(['success' => false, 'error' => 'image_not_found']);
    exit;
}

$stmt = $pdo->prepare("SELECT id FROM likes WHERE user_id=? AND image_id=?");
$stmt->execute([$user_id, $image_id]);

if ($stmt->fetch()) {
    $pdo->prepare("DELETE FROM likes WHERE user_id=? AND image_id=?")
        ->execute([$user_id, $image_id]);
    $liked = false;
} else {
    $pdo->prepare("INSERT INTO likes (user_id, image_id) VALUES (?, ?)")
        ->execute([$user_id, $image_id]);
    $liked = true;
}

$count = $pdo->prepare("SELECT COUNT(*) FROM likes WHERE image_id=?");
$count->execute([$image_id]);

echo json_encode([
    'success' => true,
    'liked' => $liked,
    'like_count' => (int)$count->fetchColumn()
]);
