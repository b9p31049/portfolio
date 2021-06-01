 # クラスの作成
class User
end

user1 = User.new
puts "#{user1.class}"

class FavoriteSpot end
class TeamMember end


# イニシャライズ(initialize)
# initのようなもの（最初に必ず呼び出される）
class Book
    def initialize
        puts 'Initialize'
    end
end
# インスタンスの作成
Book.new


#　インスタンス変数

class Book
    def initialize(name = '不明')
        @name = name
    end

    def name
        @name
    end

    def name=(new_name)
        @name = new_name
    end
end

book = Book.new
puts book.name
book.name = '初めてのRuby'
puts book.name


# これでは大変、便利なのがあるアクセサメソッド

class Book
    # 読み書き可能なメソッド作成
    attr_accessor :name, :pages
    #読み取り可能なメソッド作成
    attr_reader :price
    #書き込み可能なメソッド作成
    attr_writer :sold
end
