-- Slave :

-- wait Xms:
if(substate_delay==0) then
	delay_start=simGetSimulationTime()
	substate_delay=1
elseif(substate_delay==1) then
	if(_delay_ms(2)==1) then
		-- waited
		substate_delay=0

		-- Code after the "sleep":				
		------------------------------------------
		
		-- check distance
		get_message()
		if(message_rx[6]==1) then
			distance=message_rx[4]
			set_color(0,2,0)
			-- update distance graph
			simSetGraphUserData(DisGraphHandle,"Distance",distance)
		
			if(distance <= 40)then
				too_close=1
			end
			if(too_close==1)then
				if(distance > 60)then
					too_close=0
				else
					set_motor(cw_in_straight,ccw_in_straight)
				end
			else
				if(distance <= 60)then
					set_motor(0,ccw_in_place)
				else
					set_motor(cw_in_place,0)
				end
			end
		else
			set_color(0,0,0)
		end

		------------------------------------------
		
	end
end