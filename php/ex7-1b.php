<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>セッション</title>
</head>
<body>
    <h1>セッション</h1>
<?php

session_start();
if(isset($_SESSION["sample"])){
    echo("<p>セッションに設定された値は{$_SESSION["sample"]}です
</p>");
}else{
    echo("<p>セッションに値は設定されていません</p>");
}

?>
    <hr>
    <p><a href="ex7-1a.php">セッションに値を設定</a></p>
    <p><a href="ex7-1b.php">セッションの値を確認</a></p>
    <p><a href="ex7-1c.php">セッションの値を破棄</a></p>
</body>
</html>
