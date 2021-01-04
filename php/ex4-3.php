<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>繰り返し処理</title>
</head>
<body>
    <h1>繰り返し処理（for）</h1>
<?php

$html = "<ul>";

for($i = 1; $i <= 10; $i++){
    $html .= "<li>繰り返し処理で出力した箇条書きです({$i}/10)</li>";
    if($i >= 5) break;
}

$html .= "</ul>";
echo($html);

?>
</body