<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>配列</title>
</head>
<body>
    <h1>配列</h1>
<?php

$arr = array("茅ヶ崎","藤沢","平塚","寒川","大磯","小田原","横浜","川崎");
$key = "寒川";

if(in_array($key, $arr) == false) echo("{$key}がありません<br>");
else            echo("{$key}があります<br>");

$r = array_search($key, $arr);

echo("{$key}はキーが{$r}のところにあります<br>");

?>
</body>
</html>