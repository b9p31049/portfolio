<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>繰り返しと条件分岐</title>
</head>
<body>
    <h1>繰り返しと条件分岐</h1>
    <form method="post" action="ex4-6.php">
    行を入力：<input type="number" name="row">
    列を入力：<input type="number" name="col">
    <input type="submit" value="描画">
  </form>

<table>
<table border="1">

<?php
if(isset($_POST["row"],$_POST["col"])){
    $row = $_POST["row"];
    $col = $_POST["col"];

    for($i = 1; $i <= $col; $i++){
        echo("<tr>");
        for($j = 1; $j <= $row; $j++){      
            if($j % 2 ==0) {$style = "bgcolor=\"green\"";}
            else        {$style = "bgcolor=\"blue\"";}
            echo("<td {$style}> {$i}-{$j} </td>");
        }
        echo("</tr>");
    }
}
?>

</table>

</body>
</html>