VPATH=test:include

TEST=example
TARGET=pushNotification

ALL:$(TEST) $(TARGET)

$(TEST): example.cpp
	g++ test/example.cpp -o $(TEST) -lssl -g
	mv $(TEST) tmp
$(TARGET): main.cpp pushNotification.h
	g++ test/main.cpp -o $(TARGET) -lssl -g
	mv $(TARGET) tmp

clean:
	rm -rf $(TARGET) $(TEST) *.o
	cd tmp && rm -rf $(TARGET) $(TEST) *.o
e:
	cd tmp && ./$(TARGET)
