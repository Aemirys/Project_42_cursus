<?php
header("Content-Type: text/html; charset=UTF-8");

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (!empty($_POST["message"])) {
        $message = htmlspecialchars($_POST["message"]);
        echo "<h2>Message reçu :</h2>";
        echo "<p>$message</p>";
    }
} else {
    echo "<h2>Veuillez envoyer une requête POST</h2>";
}
?>
