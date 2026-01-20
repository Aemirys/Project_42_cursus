<?php

function ensure_directories(): void
{
    $dirs = [
        __DIR__ . '/../../public/uploads',
        __DIR__ . '/../../public/avatar',
        __DIR__ . '/../../public/thumbs',
    ];

    foreach ($dirs as $dir) {
        if (!is_dir($dir) && !mkdir($dir, 0777, true)) {
            throw new RuntimeException("Impossible de créer le dossier $dir");
        }
    }
}
