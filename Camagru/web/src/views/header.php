<?php if (session_status() === PHP_SESSION_NONE) session_start(); ?>
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Camagru</title>

    <link rel="stylesheet" href="/assets/style.css?v=<?= filemtime(__DIR__ . '/../../public/assets/style.css') ?>">

    <?php if (isset($page) && $page === 'gallery'): ?>
        <link rel="stylesheet" href="/assets/gallery.css?v=<?= time() ?>">



    <?php endif; ?>

    <?php if (isset($page) && $page === 'camera'): ?>
        <link rel="stylesheet" href="/assets/camera.css">
    <?php endif; ?>

    <script defer src="/assets/balloons.js"></script>
</head>
<body>

<div class="cloud cloud1"></div>
<div class="cloud cloud2"></div>
<div class="cloud cloud3"></div>

<div class="balloon-bg"></div>

<div id="balloon-container"></div>

<header class="site-header">
    <div class="header-container">

        <a href="/index.php" class="logo-title">
            <img src="/assets/house_up.png" alt="Maison Là-Haut" class="logo">
            <span class="site-title">Camagru</span>
        </a>

        <nav class="header-right">
            <?php if (isset($_SESSION['user_id'])): ?>
                <span class="welcome">
                    Bonjour <strong><?= htmlspecialchars($_SESSION['username']) ?></strong>
                </span>
                <a href="/gallery.php">Galerie</a>
                <a href="/camera.php">Caméra</a>
                <a href="/profile.php">Profil</a>
                <a href="/logout.php">Déconnexion</a>
            <?php else: ?>
                <a href="/login.php">Connexion</a>
                <a href="/register.php">Inscription</a>
            <?php endif; ?>
        </nav>

    </div>
</header>

<main class="container <?= isset($page) ? 'page-' . htmlspecialchars($page) : '' ?>">