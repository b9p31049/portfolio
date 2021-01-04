<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>データベース</title>
</head>
<body>
    <h1>データベース</h1>
    <hr>
<?php
$f = array();
$f1 = "<form method='post' action='ex12-1b.php'>";
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
    $html .= "<td>{$f1}{$f2}<input type='submit' value='更新'>{$f3}</td>";
    $html .= "</tr>";
}
$html .= "</table>";
echo($html);
?>
</body>
</html>
