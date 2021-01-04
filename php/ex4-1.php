<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>繰り返し処理</title>
</head>
<body>
    <h1>繰り返し処理（while）</h1>
<?php

    $i = 1;

$html = "<ul>";

while($i <= 10){
$html .= "<li>繰り返し処理で出力した箇条書きです({$i}/10)</li>";
$i++;
}

$html .= "</ul>";
echo($html);

?>
</body>
</html>
