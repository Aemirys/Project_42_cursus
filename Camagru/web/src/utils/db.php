<?php

function env(string $key, ?string $default = null): ?string {
    $v = getenv($key);
    if ($v === false || $v === '') return $default;
    return $v;
}

function get_db(): PDO {
    static $pdo = null;
    if ($pdo) return $pdo;

    $host = env('DB_HOST', 'db');
    $port = env('DB_PORT', '3306');
    $name = env('DB_NAME', 'camagru');
    $user = env('DB_USER', 'camagru');
    $pass = env('DB_PASS', 'camagru');

    $dsn = "mysql:host={$host};port={$port};dbname={$name};charset=utf8mb4";

    $tries = 10;
    while ($tries--) {
        try {
            $pdo = new PDO($dsn, $user, $pass, [
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
                PDO::ATTR_EMULATE_PREPARES => false,
            ]);
            return $pdo;
        } catch (PDOException $e) {
            if ($tries === 0) {
                throw $e;
            }
            usleep(300_000);
        }
    }

    throw new RuntimeException('DB connection failed');
}
