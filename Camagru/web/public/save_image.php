<?php
session_start();

require_once '../src/utils/auth.php';
require_once '../src/utils/db.php';
require_once '../src/utils/csrf.php';
require_login();

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    $_SESSION['error'] = "Méthode invalide";
    header('Location: camera.php');
    exit;
}

if (!verify_csrf($_POST['csrf'] ?? '')) {
    $_SESSION['error'] = "CSRF invalide";
    header('Location: camera.php');
    exit;
}

/* ===================== FILTRES AUTORISÉS ===================== */
$allowed_filters = ['balloon.png','glasses.png','house.png','knot.png'];

$filter = $_POST['filter'] ?? '';
$has_filter = in_array($filter, $allowed_filters, true);

/* ===================== COORDONNÉES NORMALISÉES ===================== */
$fx = (float)($_POST['fx'] ?? 0.5);
$fy = (float)($_POST['fy'] ?? 0.5);
$fscale = (float)($_POST['fscale'] ?? 0.35);

if ($fx < 0 || $fx > 1) $fx = 0.5;
if ($fy < 0 || $fy > 1) $fy = 0.5;
if ($fscale < 0.05) $fscale = 0.05;
if ($fscale > 1.2) $fscale = 1.2;

/* ===================== IMAGE SOURCE ===================== */
$base_img = null;

/* Webcam (base64) */
if (!empty($_POST['image_data'])) {
    $s = (string)$_POST['image_data'];

    // limite taille base64 (~10MB)
    if (strlen($s) > 10_000_000) {
        $_SESSION['error'] = "Image trop lourde";
        header('Location: camera.php');
        exit;
    }

    if (preg_match('#^data:image/(png|jpeg);base64,#', $s) !== 1) {
        $_SESSION['error'] = "Format image invalide";
        header('Location: camera.php');
        exit;
    }

    $parts = explode(',', $s, 2);
    $bin = base64_decode($parts[1] ?? '', true);
    if ($bin !== false) {
        $base_img = imagecreatefromstring($bin);
    }
}

/* Upload fallback */
if (
    !$base_img &&
    isset($_FILES['upload_image']) &&
    $_FILES['upload_image']['error'] === UPLOAD_ERR_OK
) {
    $tmp  = $_FILES['upload_image']['tmp_name'];
    $size = (int)($_FILES['upload_image']['size'] ?? 0);

    if (!is_uploaded_file($tmp)) {
        $_SESSION['error'] = "Upload invalide";
        header('Location: camera.php');
        exit;
    }

    // Limite taille upload (ex: 5 Mo)
    if ($size <= 0 || $size > 5 * 1024 * 1024) {
        $_SESSION['error'] = "Fichier trop lourd (max 5 Mo)";
        header('Location: camera.php');
        exit;
    }

    // Vérifie que c'est vraiment une image
    if (@getimagesize($tmp) === false) {
        $_SESSION['error'] = "Le fichier n'est pas une image valide";
        header('Location: camera.php');
        exit;
    }

    // Mime réel
    $fi = finfo_open(FILEINFO_MIME_TYPE);
    $mime = $fi ? finfo_file($fi, $tmp) : '';
    if ($fi) finfo_close($fi);

    if (!in_array($mime, ['image/png','image/jpeg'], true)) {
        $_SESSION['error'] = "Format refusé (PNG/JPG uniquement)";
        header('Location: camera.php');
        exit;
    }

    $data = file_get_contents($tmp);
    if ($data !== false) {
        $base_img = imagecreatefromstring($data);
    }
}

if (!$base_img) {
    $_SESSION['error'] = "Aucune image valide";
    header('Location: camera.php');
    exit;
}

/* ===================== LIMIT IMAGE SIZE ===================== */
$max_width  = 1200;
$max_height = 1200;

$w = imagesx($base_img);
$h = imagesy($base_img);

if ($w <= 0 || $h <= 0) {
    imagedestroy($base_img);
    $_SESSION['error'] = "Image invalide";
    header('Location: camera.php');
    exit;
}

/* Refus images déraisonnables */
if ($w > 6000 || $h > 6000) {
    imagedestroy($base_img);
    $_SESSION['error'] = "Image trop grande";
    header('Location: camera.php');
    exit;
}

/* Redimensionnement si nécessaire */
if ($w > $max_width || $h > $max_height) {
    $ratio = min($max_width / $w, $max_height / $h);

    $new_w = (int)($w * $ratio);
    $new_h = (int)($h * $ratio);

    $resized = imagecreatetruecolor($new_w, $new_h);
    imagecopyresampled(
        $resized,
        $base_img,
        0, 0, 0, 0,
        $new_w, $new_h,
        $w, $h
    );

    imagedestroy($base_img);
    $base_img = $resized;

    $w = $new_w;
    $h = $new_h;
}

/* ===================== IMAGE FINALE ===================== */
$final = imagecreatetruecolor($w, $h);
imagecopy($final, $base_img, 0, 0, 0, 0, $w, $h);
imagedestroy($base_img);

/* ===================== OVERLAY SERVEUR ===================== */
if ($has_filter) {
    $filter_path = __DIR__ . '/filters/' . $filter;
    if (!is_file($filter_path)) {
        imagedestroy($final);
        $_SESSION['error'] = "Filtre introuvable";
        header('Location: camera.php');
        exit;
    }

    $overlay = imagecreatefrompng($filter_path);
    if (!$overlay) {
        imagedestroy($final);
        $_SESSION['error'] = "Filtre invalide";
        header('Location: camera.php');
        exit;
    }

    imagesavealpha($overlay, true);

    $dw = (int)($w * $fscale);
    $dh = (int)(imagesy($overlay) * ($dw / imagesx($overlay)));

    $centerX = (int)($fx * $w);
    $centerY = (int)($fy * $h);

    $x = (int)($centerX - $dw / 2);
    $y = (int)($centerY - $dh / 2);

    imagecopyresampled(
        $final,
        $overlay,
        $x, $y,
        0, 0,
        $dw, $dh,
        imagesx($overlay),
        imagesy($overlay)
    );

    imagedestroy($overlay);
}

/* ===================== SAUVEGARDE IMAGE ===================== */
$filename = uniqid('img_', true) . '.png';
$save_path = __DIR__ . '/uploads/' . $filename;

if (!imagepng($final, $save_path)) {
    imagedestroy($final);
    $_SESSION['error'] = "Erreur lors de la sauvegarde";
    header('Location: camera.php');
    exit;
}
imagedestroy($final);

/* ===================== THUMBNAIL ===================== */
$src = imagecreatefrompng($save_path);
if (!$src) {
    $_SESSION['error'] = "Erreur création miniature";
    header('Location: camera.php');
    exit;
}

$tw = 240;
$th = (int)(imagesy($src) * ($tw / imagesx($src)));

$thumb = imagecreatetruecolor($tw, $th);
imagecopyresampled(
    $thumb,
    $src,
    0, 0,
    0, 0,
    $tw, $th,
    imagesx($src),
    imagesy($src)
);

$thumb_name = uniqid('th_', true) . '.png';
$thumb_path = __DIR__ . '/thumbs/' . $thumb_name;

if (!imagepng($thumb, $thumb_path)) {
    imagedestroy($src);
    imagedestroy($thumb);
    $_SESSION['error'] = "Erreur sauvegarde miniature";
    header('Location: camera.php');
    exit;
}

imagedestroy($src);
imagedestroy($thumb);

/* ===================== DB ===================== */
$pdo = get_db();
$stmt = $pdo->prepare("
    INSERT INTO images (user_id, filename, thumb)
    VALUES (?, ?, ?)
");
$stmt->execute([
    (int)$_SESSION['user_id'],
    $filename,
    $thumb_name
]);

$_SESSION['success'] = "Image enregistrée";
header('Location: camera.php');
exit;
