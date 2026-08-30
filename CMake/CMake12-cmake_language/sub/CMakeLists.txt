#1读取初始值
message("1 sub : ${SCOP}")

#2修改值
set(SCOP "Sub Scop" PARENT_SCOPE)

#3查看修改后的值
message("2 sub : ${SCOP}")