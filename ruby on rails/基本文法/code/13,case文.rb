# case文
# if文の簡易的版

value = 5

# １、どれかに該当しているかの場合
symbol = case value
            when 1
                :one
            when 2
                :two
            when 3
                :three
            when 4
                :four
            when 5
                :five
            else
                :other
        end
puts symbol


# ２、rangeオブジェクトも可能

value = 3

symbol = case value
            when 1..5
                :low
            when 6..10
                :high
            else
                :invalid
        end

puts symbol


# ３、一つずつ書く方法

value = 'りんご'

symbol = case value
            when 'りんご', 'なし', 'キウイ', 'もも'
                '果物'
            when 'キャベツ', 'トマト', 'ねぎ'
                '野菜'
            else
                '該当なし'
        end

puts symbol