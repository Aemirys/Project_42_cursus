<?php
session_start();

require_once '../src/utils/auth.php';
require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';

require_login();

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    header('Location: /gallery.php');
    exit;
}

if (!verify_csrf($_POST['csrf'] ?? '')) {
    header('Location: /gallery.php');
    exit;
}

$image_id = (int)($_POST['image_id'] ?? 0);
if ($image_id <= 0) {
    header('Location: /gallery.php');
    exit;
}

$pdo = get_db();


$stmt = $pdo->prepare("
    SELECT filename, thumb, user_id
    FROM images
    WHERE id = ?
    LIMIT 1
");
$stmt->execute([$image_id]);
$image = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$image) {
    header('Location: /gallery.php');
    exit;
}

if ((int)$image['user_id'] !== (int)$_SESSION['user_id']) {
    header('Location: /gallery.php');
    exit;
}


$imgPath   = __DIR__ . '/uploads/' . $image['filename'];
$thumbPath = __DIR__ . '/thumbs/' . $image['thumb'];

try {
    $pdo->beginTransaction();

    $del = $pdo->prepare("DELETE FROM images WHERE id=?");
    $del->execute([$image_id]);

    $pdo->commit();
} catch (Throwable $e) {
    if ($pdo->inTransaction()) $pdo->rollBack();
    header('Location: /gallery.php');
    exit;
}


if (is_file($imgPath))   { @unlink($imgPath); }
if (is_file($thumbPath)) { @unlink($thumbPath); }

header('Location: /gallery.php');
exit;
