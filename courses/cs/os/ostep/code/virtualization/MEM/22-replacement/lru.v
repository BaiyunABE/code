module lru(CLK, visit, data, miss);
	parameter CACHE_SIZE = 16;
	parameter CACHE_LENGTH = 64;

	input CLK;
	input visit;
	input [CACHE_LENGTH - 1:0] data;
	output miss;

	reg [CACHE_LENGTH - 1:0] cache [0:CACHE_SIZE - 1];
	reg miss_temp [0:CACHE_SIZE - 1];

	integer i;

	always @ (*)
	begin
		miss_temp[0] = (data != cache[0] && visit);
		for (i = 0; i < CACHE_SIZE - 1; i = i + 1)
		begin
			miss_temp[i + 1] = (data != cache[i + 1] && miss_temp[i]);
		end
	end

	always @ (posedge CLK)
	begin
		if (visit)
		begin
			cache[0] <= data;
		end
		
		for (i = 0; i < CACHE_SIZE - 1; i = i + 1)
		begin
			if (miss_temp[i])
			begin
				cache[i + 1] <= cache[i];
			end
		end
	end

	assign miss = miss_temp[CACHE_SIZE - 1];

endmodule

