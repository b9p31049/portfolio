<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>繰り返しと条件分岐</title>
</head>
<body>
    <h1>繰り返しと条件分岐</h1>
    <form method="post" action="ex4-5.php">
    数を入力：<input type="number" name="r">
    <input type="submit" value="描画">
  </form>

<?php
if(isset($_POST["r"])){
    $r = $_POST["r"];
    $html = "<ul>";
    for($i = 1; $i <= $r; $i++){
        if($i % 2 == 0) $style = " style='color:red;'";
        else $style = "";
        $html .= "<li{$style}>繰り返し処理で出力した箇条書きです({$i}/{$r})</li>";
    }
    $html .= "</ul>";
    echo($html);
}
?>
</body>
</html>
