<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>セッション</title>
</head>
<body>
    <h1>セッション</h1>
    <form method="post" action="ex7-5a.php">
        氏名：<input name="si"><br>
        学籍番号：<input name="g"><br>
        メール：<input name="m"><br>
        <input type="submit" value="設定">
    </form>
<?php

include("ex7-5.php");
    $arr = array();
    $arr["name"] = "si";
    $arr["no"] = "g";
    $arr["mail"] = "m";
    $s = new student($arr);

session_start();
    $_SESSION["sample"] = $s;
    echo("<p>セッションにクラスを設定しました</p>");
?>

<hr>
<p><a href="ex7-5a.php">セッションに値を設定</a></p>
<p><a href="ex7-5b.php">セッションの値を確認</a></p>
</body>
</html>