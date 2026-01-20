<?php

function send_mail(string $to, string $subject, string $body): bool
{
    // SMTP (MailHog en local)
    $host = 'mailhog';
    $port = 1025;

    // Expéditeur
    $from = 'no-reply@camagru.local';

    // Connexion SMTP
    $fp = fsockopen($host, $port, $errno, $errstr, 5);
    if (!$fp) {
        return false;
    }

    // Helpers
    $read = function () use ($fp) {
        return fgets($fp, 512);
    };

    $write = function (string $cmd) use ($fp) {
        fwrite($fp, $cmd . "\r\n");
    };

    $expectOk = function () use ($read) {
        $line = $read();
        if ($line === false) {
            return false;
        }
        $code = (int) substr($line, 0, 3);
        return ($code >= 200 && $code < 400);
    };

    // Handshake SMTP
    if (!$expectOk())               { fclose($fp); return false; }
    $write("HELO localhost");        if (!$expectOk()) { fclose($fp); return false; }
    $write("MAIL FROM:<$from>");     if (!$expectOk()) { fclose($fp); return false; }
    $write("RCPT TO:<$to>");         if (!$expectOk()) { fclose($fp); return false; }
    $write("DATA");                  if (!$expectOk()) { fclose($fp); return false; }

    // Sécurité : éviter header injection
    $subject = str_replace(["\r", "\n"], '', $subject);

    // Dot-stuffing (RFC SMTP)
    $body = preg_replace('/^\./m', '..', $body);

    // Headers
    $headers =
        "From: $from\r\n" .
        "To: $to\r\n" .
        "Subject: $subject\r\n" .
        "MIME-Version: 1.0\r\n" .
        "Content-Type: text/plain; charset=UTF-8\r\n" .
        "Content-Transfer-Encoding: 8bit\r\n";

    // Message final
    $message = $headers . "\r\n" . $body . "\r\n.\r\n";

    // Envoi
    fwrite($fp, $message);
    if (!$expectOk()) {
        fclose($fp);
        return false;
    }

    // Fermeture
    $write("QUIT");
    fclose($fp);

    return true;
}