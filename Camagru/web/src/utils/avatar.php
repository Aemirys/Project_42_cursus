<?php

function handle_avatar_upload(int $user_id): ?string
{
    if (!isset($_FILES['avatar']) || $_FILES['avatar']['error'] === UPLOAD_ERR_NO_FILE) {
        return null;
    }

    $file = $_FILES['avatar'];

    // Erreurs PHP
    if ($file['error'] !== UPLOAD_ERR_OK) {
        return null;
    }

    // Vérifier MIME réel
    $finfo = new finfo(FILEINFO_MIME_TYPE);
    $mime  = $finfo->file($file['tmp_name']);

    if (!in_array($mime, ['image/jpeg', 'image/png'], true)) {
        return null;
    }

    // Lire dimensions SANS charger toute l’image
    [$width, $height] = getimagesize($file['tmp_name']);

    // Protection RAM
    if ($width > 6000 || $height > 6000) {
        return null;
    }

    // Création ressource image
    if ($mime === 'image/jpeg') {
        $src = imagecreatefromjpeg($file['tmp_name']);
        $ext = 'jpg';
    } else {
        $src = imagecreatefrompng($file['tmp_name']);
        $ext = 'png';
    }

    if (!$src) {
        return null;
    }

    // Taille avatar finale
    $maxSize = 512;
    $ratio = min($maxSize / $width, $maxSize / $height, 1);

    $newW = (int)($width * $ratio);
    $newH = (int)($height * $ratio);

    $dst = imagecreatetruecolor($newW, $newH);

    // Transparence PNG
    if ($mime === 'image/png') {
        imagealphablending($dst, false);
        imagesavealpha($dst, true);
        $transparent = imagecolorallocatealpha($dst, 0, 0, 0, 127);
        imagefill($dst, 0, 0, $transparent);
    }

    imagecopyresampled(
        $dst,
        $src,
        0, 0, 0, 0,
        $newW, $newH,
        $width, $height
    );

    $uploadDir = __DIR__ . '/../../public/avatar';

    // Nettoyage ancien avatar
    $pdo = get_db();
    $stmt = $pdo->prepare("SELECT avatar_path FROM users WHERE id=?");
    $stmt->execute([$user_id]);
    if ($old = $stmt->fetchColumn()) {
        $oldFile = $uploadDir . '/' . $old;
        if (is_file($oldFile)) {
            unlink($oldFile);
        }
    }

    // Nom de fichier sécurisé
    $filename = 'avatar_' . $user_id . '_' . bin2hex(random_bytes(8)) . '.' . $ext;
    $destination = $uploadDir . '/' . $filename;

    // Sauvegarde
    $saved = ($mime === 'image/jpeg')
        ? imagejpeg($dst, $destination, 85)
        : imagepng($dst, $destination, 6);

    imagedestroy($src);
    imagedestroy($dst);

    return $saved ? $filename : null;
}
