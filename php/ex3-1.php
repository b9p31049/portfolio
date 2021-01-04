<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>変数</title>
</head>
<body>
    <h1>変数</h1>
<?php

$d1 = 15; //変数d1に整数値の15を代入
$d2 = "Web Programing"; //変数d2に文字列を代入
$d3 = true; //変数d3にbool型を代入
$d4 = 12.345; //変数d4に浮動小数の値を代入
$d5 = (string)$d1; //変数d5に変数d1の内容を文字に変換して代入

//変数d1～d5のデータ型を確認
echo("{$d1}のデータ型は，「" . gettype($d1) . "」です<br>");
echo("{$d2}のデータ型は，「" . gettype($d2) . "」です<br>");
echo("{$d3}のデータ型は，「" . gettype($d3) . "」です<br>");
echo("{$d4}のデータ型は，「" . gettype($d4) . "」です<br>");
echo("{$d5}のデータ型は，「" . gettype($d5) . "」です<br>");

?>
</body>
</html>