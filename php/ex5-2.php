<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>配列</title>
</head>
<body>
    <h1>配列</h1>
<?php

$arr1 = array(1,2,3,4,5);
$arr2 = array(6,7,8,9);
$arr3 = array_merge($arr1, $arr2);
foreach($arr3 as $k => $v){
echo("変数arr3のキー{$k}の値は{$v}です<br>");
}
echo("変数arr1の値の個数は" . count($arr1) . "です<br>");
echo("変数arr2の値の個数は" . count($arr2) . "です<br>");
echo("変数arr3の値の個数は" . count($arr3) . "です<br>");
echo("変数arr3の値を全部足すと" . array_sum($arr3) . "です<br>");

?>
</body>
</html>
