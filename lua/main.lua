--
-- Created by IntelliJ IDEA.
-- User: pogam-_g
-- Date: 6/1/16
-- Time: 3:56 PM
-- To change this template use File | Settings | File Templates.
--

function main()
    while ia.dead() == false do
        local x = ia.get_x()
        local y = ia.get_y()

        if ia.get_case_content(x - ia.get_block_size(), y) == "BOX" then
            ia.put_bomb()
            while ia.get_x() ~= x + 50 do
                ia.move_right()
            end
        else
            ia.move_left()
        end
    end
end
