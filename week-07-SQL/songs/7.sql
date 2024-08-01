SELECT avg(songs.energy) FROM artists JOIN songs ON artists.id = songs.artist_id where artists.name= "Drake";
