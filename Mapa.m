coords = []
for i=1:20  
    rng('shuffle')
    r1 = rand(2,1);
    newCoords = [r1(1)+45; r1(2)+130]
    coords = [coords, newCoords]
    maximo = [max(coords(1,:)'), max(coords(2,:)')]
    minimo = [min(coords(1,:)'), min(coords(2,:)')]
    
    geoplot (coords (1,:), coords (2,:), '-*')
    geolimits ([minimo(1)-0.001 maximo(1)+0.001],[minimo(2)-0.001 maximo(2)+0.001])
    geobasemap topographic

  end
