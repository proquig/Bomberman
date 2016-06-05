--
-- Created by IntelliJ IDEA.
-- User: pogam-_g
-- Date: 6/1/16
-- Time: 3:56 PM
-- To change this template use File | Settings | File Templates.
--

function top()
    while 1 and ia.dead() == false do
        local x = ia.get_x()
        local y = ia.get_y()

        local object = ia.get_case_content(x, ia.get_round_position(y + ia.get_block_size()))

        if object == "BOX" then
            ia.put_bomb()
            local t = os.date("*t")

            while os.date("*t").sec < ((t.sec) + 3) do
                ia.move_bottom()
            end
            return
        elseif object == "BRICK" then
            return
        else
            ia.move_top()
        end
    end
end

function bottom()
    while 1 and ia.dead() == false do
        local x = ia.get_x()
        local y = ia.get_y()

        local object = ia.get_case_content(x, ia.get_round_position(y - ia.get_block_size()))

        if object == "BOX" then
            ia.put_bomb()
            local t = os.date("*t")

            while os.date("*t").sec < ((t.sec) + 3) do
                ia.move_top()
            end
            return
        elseif object == "BRICK" then
            return
        else
            ia.move_bottom()
        end
    end
end

function left()
    while 1 and ia.dead() == false do
        local x = ia.get_x()
        local y = ia.get_y()

        local object = ia.get_case_content(ia.get_round_position(x - ia.get_block_size()), y)

        if object == "BOX" then
            ia.put_bomb()
            local t = os.date("*t")

            while os.date("*t").sec < ((t.sec) + 3) do
                ia.move_right()
            end
            return
        elseif object == "BRICK" then
            return
        else
            ia.move_left()
        end
    end
end

function right()
    while 1 and ia.dead() == false do
        local x = ia.get_x()
        local y = ia.get_y()

        local object = ia.get_case_content(ia.get_round_position(x + ia.get_block_size()), y)

        if object == "BOX" then
            ia.put_bomb()
            local t = os.date("*t")

            while os.date("*t").sec < ((t.sec) + 3) do
                ia.move_left()
            end
            return
        elseif object == "BRICK" then
            return
        else
            ia.move_right()
        end
    end
end

function main()
    local r = 0
    local prev = 0

    while ia.dead() == false do
        local r = math.random(4)
        if prev == 0 or (prev ~= 0 and r ~= prev) then
            if r == 1 then
                left()
            elseif r == 2 then
                right()
            elseif r == 3 then
                bottom()
            else
                top()
            end
            prev = r
        end
    end
end
