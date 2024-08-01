SELECT songs.name
FROM artists
JOIN songs ON artists.id = songs.artist_id
WHERE artists.name = "Post Malone";

-- SELECT songs.name: We want to get the names of the songs.
-- FROM artists: Start with the artists table.
-- JOIN songs ON artists.id = songs.artist_id: Join the songs table where the artist_id in the songs table matches the id in the artists table.
-- WHERE artists.name = 'Post Malone': Filter the results to only include the rows where the artist's name matches 'Post Malone'.
