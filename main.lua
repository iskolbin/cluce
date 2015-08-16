print('hi from lua')
print('cluce', cluce.run)

cluce.init()

local b = cluce.createBatch()
local t = cluce.loadTexture('test.png')
local f = cluce.createFramesList()
cluce.addUnitFrame(f,0,640,480,0)
local w = cluce.createWidget(b,f)
cluce.addBatch(b)

cluce.addAttr(w,0,50)

cluce.run()
