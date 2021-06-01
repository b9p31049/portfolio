# 例外処理
# プログラミのエラーにより、処理が終了してしまう現象

# 書き方
#begin
# 例外が起こるかも知れないコード
#rescue => error # 変数(例外オブジェクトの代入)
# 例外が発生した時のコード


    # 1, NameError : 定義していない変数の呼び出しなど

    # 2, １/0(０で割り算) →　ZeroDivisionError

    # 例外処理　→　begin, rescue
    # 例外オブジェクトの表示 p e　
       
        # 1,内容の表示　backtrace
        begin
            val = 10 / 0
            puts val
        rescue => e
            p e.backtrace
        end

        # 2,内藤全部の表示　full_message
        begin
            val = 10 / 0
            puts val
        rescue => e
            p e.full_message
        end
  
    begin
        hoge
        10/0
    rescue ZeroDivisionError => e
        puts '0で割ってはいけません'
    rescue => e
        puts 'その他のエラー'
    end

    puts '終了'


    # retry(もう一度実行)
    num = 0

    begin
        p 10 / num
    rescue ZeroDivisionError => e
        p e
        num = 2
        retry
    end

    puts '終了'


    # 一時的に例外の発生
    # raise (RuntimeError)
    # raise ZeroDivisionError (ZeroDivisionError)

    # raiseを使うとき、ある条件に置いて明示的にエラーを出したい場合

    begin
        raise 
    rescue => e
        p e
    end

    # ensureは、最後に必ず実行される
    begin
        puts '例外なし'
    rescue => e
        p e
    ensure
        puts 'ensureが実行されました'
    end