<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>データベース</title>
</head>
<body>
    <h1>データベース</h1>
<?php
$dsn = "mysql:dbname=sample01;host=localhost";
$my = new PDO($dsn, "wp", "wp");
$sql = "SELECT * FROM 授業;";
$st = $my->prepare($sql);
$st->execute();
$html = "<table border='1'><tr><th>授業名</th><th>教員</th><th>曜日</th><th>時間</th></tr>";
while($row = $st->fetch(PDO::FETCH_ASSOC)){
    $html .= "<tr>";
    foreach($row as $item) $html .= "<td>{$item}</td>";
    $html .= "</tr>";
}
$html .= "</table>";
echo($html);
?>
</body>
</html>
