<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>繰り返しと条件分岐</title>
</head>
<body>
    <h1>繰り返しと条件分岐</h1>
    <form method="post" action="ex4-7.php">
    行を入力：<input type="number" name="row">
    列を入力：<input type="number" name="col">
    <input type="submit" value="描画">
  </form>


<?php
if(isset($_POST["row"],$_POST["col"])){
    $row = $_POST["row"];
    $col = $_POST["col"];   
}
?>
<?phpfor($i = 1; $i <= $col; $i++){ ?>
    <?php    for($j = 1; $j <= $row; $j++){  ?>
        <?phpif($j % 2 == 0) $style = "style ='background-color:green;'";
        else $style = "style ='background-color:blue;'";    ?>
        <div style= <?php echo $style ?> > <?php echo $i ?>-<?php echo $j ?> </div>
    <?php   }  ?>
    <br>
<?php   }   ?>




</body>
</html>