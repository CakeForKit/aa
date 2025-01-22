SRCF := ./src
INCF := ./inc
OUTF := ./out

CC := g++ -I $(INCF)
SRCS := $(wildcard $(SRCF)/*.cpp)
OBJS := $(SRCS:$(SRCF)/%.c=$(OUTF)/%.o)

app.exe : $(OBJS)
	$(CC) $^ -o $@

run : app.exe
	./app.exe
	python3 create_main_log.py

$(OUTF)/%.o : $(SRCF)/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTF)/%.d : $(SRCF)/%.cpp
	$(CC) -MM $< > $@

include $(SRCS:$(SRCF)/%.cpp=$(OUTF)/%.d)

clean :
	rm $(OUTF)/* data_out/* ./app.exe