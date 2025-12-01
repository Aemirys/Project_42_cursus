<?php
$files = scandir('contact');
foreach ($files as $file) {
    if ($file !== '.' && $file !== '..') {
        echo "<div>";
        echo "<p>$file</p>";
        echo "<button class='delete-btn' data-file='$file'>Supprimer</button>";
        echo "</div>";
    }
}
?>
