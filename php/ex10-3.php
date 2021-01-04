<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>データベース</title>
</head>
<body>
    <h1>データベース</h1>
    <hr>
    <form method="post" action="ex10-3.php">
        授業名：<input name="q"><br>
        並び変え：<select name=”nara”>
        <option value=”j”>授業</option>
        <option value=”k”>教員</option>
        <option value=”y”>曜日</option>
        <option value=”z”>時間</option>
        </select><br>
        <input type="submit" value="検索">
    </form>
    
<?php
if(isset($_POST["q"])){
    $arr = array(sprintf('%%%s%%', $_POST["q"]));
    $dsn = "mysql:dbname=sample01;host=localhost";
    $my = new PDO($dsn, "wp", "wp");
    $sql = "SELECT * FROM 授業 WHERE 授業 like ? ORDER BY 時間 DESC;";
    $st = $my->prepare($sql);
    $st->execute($arr);
    $html = "<table border='1'><tr><th>授業</th><th>教員</th><th>曜日</th><th>時間</th></tr>";
    while($row = $st->fetch(PDO::FETCH_ASSOC)){
        $html .= "<tr>";
        foreach($row as $item) $html .= "<td>{$item}</td>";
        $html .= "</tr>";
    }
    $html .= "</table>";
    echo($html);
}
if(isset($_POST["nara"])){
    if($POST["nara"] == 'j'){
        $sql = "SELECT * FROM 授業 WHERE 授業 like ? ORDER BY 授業 DESC;";
    }
    elseif($POST["nara"] == 'k'){
        $sql = "SELECT * FROM 授業 WHERE 授業 like ? ORDER BY 教員 DESC;";
    }
    elseif($POST["nara"] == 'y'){
        $sql = "SELECT * FROM 授業 WHERE 授業 like ? ORDER BY 曜日 DESC;";
    }
    else{
        $sql = "SELECT * FROM 授業 WHERE 授業 like ? ORDER BY 時間 DESC;";
    }
}


?>
</body>
</html>