CPP = g++

CPP_FLAGS = -Wall -g

TARGETS = frame_buffer_tester

frame_buffer_tester : frame_buffer_tester.o frame_buffer.o
	$(CPP) $(CPP_FLAGS) -o $@ $<

frame_buffer_tester.o : frame_buffer_tester.cc
	$(CPP) $(CPP_FLAGS) -c $<

frame_buffer.o : frame_buffer_tester.cc 
	$(CPP) $(CPP_FLAGS) -c $<

