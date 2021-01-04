<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>セッション</title>
</head>
<body>
    <h1>セッション</h1>
    <form method="post" action="ex7-2a.php">
        氏名：<input name="si"><br>
        学籍番号：<input name="g"><br>
        メール：<input name="m"><br>
        <input type="submit" value="設定">
    </form>
<?php

class student{
    var $simei;
    var $no;
    var $mail;
    function __construct($arr){
        foreach($arr as $k => $v) $this -> $k = $v;
    }
}

$arr = array();
$arr["simei"] = $_POST["si"];
$arr["no"] = $_POST["g"];
$arr["mail"] = $_POST["m"];
$s = new student($arr);

session_start();
$_SESSION["sample"] = $s;
echo("<p>セッションにクラスを設定しました</p>");

?>
    <hr>
    <p><a href="ex7-2a.php">セッションに値を設定</a></p>
    <p><a href="ex7-2b.php">セッションの値を確認</a></p>
</body>
</html>