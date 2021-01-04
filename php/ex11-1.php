<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>データベース</title>
</head>
<body>
    <h1>データベース</h1>
    <hr>
    <form method="post" action="ex11-1.php">
    授業名：<input name="q1"><br>
    教 員：<input name="q2"><br>
    曜 日：<input name="q3"><br>
    時 間：<input name="q4" type="number"><br>
    <br>
    <input type="submit" value="追加">
    </form>
<?php
if(isset($_POST["q1"], $_POST["q2"], $_POST["q3"], $_POST["q4"])){
    $arr = array($_POST["q1"], $_POST["q2"], $_POST["q3"], $_POST["q4"]);
    $dsn = "mysql:dbname=sample01;host=localhost";
    $my = new PDO($dsn, "wp", "wp");
    $sql = "INSERT INTO 授業 (授業名,教員,曜日,時間) VALUES (?,?,?,?);";
    $st = $my->prepare($sql);
    if($st->execute($arr) == false)
        echo("データの追加に失敗しました");
    else
        echo("データを追加しました");
}
$f = array();
$f1 = "<form method='post' action='ex11-2.php'>";
$f3 = "</form>";
$dsn = "mysql:dbname=sample01;host=localhost";
$my = new PDO($dsn, "wp", "wp");
$sql = "SELECT * FROM 授業;";
$st = $my->prepare($sql);
$st->execute();
$html = "<table border='1'><tr><th>授業名</th><th>教員</th><th>曜日</th><th>時間</th></tr>";
while($row = $st->fetch(PDO::FETCH_ASSOC)){
$html .= "<tr>";
$f2 = "";
foreach($row as $k => $item){
$f2 .= "<input name='{$k}' value='{$item}' type='hidden'>";
$html .= "<td>{$item}</td>";
}
$html .= "<td>{$f1}{$f2}<input type='submit' value='削除'>{$f3}</td>";
$html .= "</tr>";

include("ex11-1inc.php");
?>
</body>
</html>
