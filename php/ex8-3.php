<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>ファイル操作</title>
</head>
<body>
    <h1>ファイル操作</h1>
<?php
$fn = "ex8-3.txt";

if(file_exists($fn)){
    $f = fopen($fn, "r");
    echo("ファイル：{$fn}の内容は以下の通りです<hr>");
    $i = 1;
    while(!feof($f)){
        echo("{$i}行目：" . fgets($f) . "<br>");
        $i++;
    }
    fclose($f);
    echo("<hr>");
}else{
    echo("指定されたファイル：{$fn}は存在しません");
}
?>
</body>
</html>
