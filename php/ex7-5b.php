<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>セッション</title>
</head>
<body>
    <h1>セッション</h1>
<?php

include("ex7-5.php");

session_start();
echo($_SESSION["sample"]->name);

?>
    <hr>
    <p><a href="ex7-5a.php">セッションに値を設定</a></p>
    <p><a href="ex7-5b.php">セッションの値を確認</a></p>
</body>
</html>