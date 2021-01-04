<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>セッション</title>
</head>
<body>
    <h1>セッション</h1>
<?php

class student{
    var $simei;
    var $no;
    var $mail;
    function __construct($arr){
        foreach($arr as $k => $v) $this -> $k = $v;
    }
}

session_start();
echo($_SESSION["sample"]->simei);s
echo($_SESSION["sample"]->no);
echo($_SESSION["sample"]->mail);

?>
    <hr>
    <p><a href="ex7-2a.php">セッションに値を設定</a></p>
    <p><a href="ex7-2b.php">セッションの値を確認</a></p>
</body>
</html>
