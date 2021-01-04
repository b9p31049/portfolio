<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>配列</title>
</head>
<body>
    <h1>配列</h1>
<?php

$arr = array("a","b","c","d","e","f","g");

shuffle($arr);

foreach($arr as $k => $v){
    echo("変数arrのキー{$k}の値は{$v}です<br>");
}

echo("<hr>");

asort($arr);

foreach($arr as $k => $v){
    echo("変数arrのキー{$k}の値は{$v}です<br>");
}

?>
</body>
</html>