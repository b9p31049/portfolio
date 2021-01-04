<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>配列</title>
</head>
<body>
    <h1>配列</h1>
<?php

$sample = array(1,2,3,4,5,"aaa","bbb","ccc");
$sample[] = "さらに追加";
$sample[] = false;
$sample[] = 0x33;
$sample[20] = "値を飛ばして20に入れる";
$sample[] = "その後にキー指定なし";

var_dump($sample);

?>
</body>
</html>
