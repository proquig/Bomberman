--
-- Created by IntelliJ IDEA.
-- User: pogam-_g
-- Date: 6/1/16
-- Time: 3:56 PM
-- To change this template use File | Settings | File Templates.
--

function main()
    if ia.dead() == true then
        io.write("IA already dead ? D:\n")
    end
    while ia.dead() == false do
        ia.move("LEFT")
        ia.put_bomb()
    end
end
