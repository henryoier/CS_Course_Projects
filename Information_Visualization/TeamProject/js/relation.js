var width = 1000,
    height = 400;
var svg = d3.select("body").append("svg")
    .attr("width", width+300)
    .attr("height", height+200);

// Arrows markers

svg.append("defs")
    .append("marker")
    .attr("id", "markerEnd")
    .attr('viewBox', '0 -5 10 10')
    .attr('refX', 6)
    .attr('markerWidth', 3)
    .attr('markerHeight', 3)
    .attr('orient', 'auto')
    .append('svg:path')
    .attr('d', 'M0,-5L10,0L0,5')
    .attr('fill', '#000');

svg.append("defs")
    .append("marker")
    .attr("id", "markerStart")
    .attr('viewBox', '0 -5 10 10')
    .attr('refX', 4)
    .attr('markerWidth', 3)
    .attr('markerHeight', 3)
    .attr('orient', 'auto')
    .append('svg:path')
    .attr('d', 'M10,-5L0,0L10,5')
    .attr('fill', '#000');

//Create main line
svg.append("line")
    .attr("x1",2*width/8+50)
    .attr("y1",height/4-50)
    .attr("x2",2*width/8+50)
    .attr("y2",4*height/4-93);

// Create Henk Bodrogi
var Henk_Bodrogi = svg
    .append("rect")
    .attr("class", "bold")
    .attr("x", 1*width/8)
    .attr("y", 2*height/4-40)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10);

svg.append("text")
    .attr("x", 1*width/8 )
    .attr("y", 2*height/4-40)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .style("text-anchor", "middle")
    .text("Henk")
    .append("tspan")
    .attr("x", 1*width/8 )
    .attr("y", 2*height/4-25)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .text("Bodrogi");

//Create line to main
svg.append("line")
    .attr("x1",1*width/8+100)
    .attr("y1",2*height/4-20)
    .attr("x2",2*width/8+50)
    .attr("y2",2*height/4-20);

//Create Carmine Osvaldo
var Carmine_Osvaldo = svg
    .append("rect")
    .attr("x", 3*width/8)
    .attr("y", height/4-70)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10);

svg.append("text")
    .attr("x", 3*width/8 )
    .attr("y", height/4-70)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .style("text-anchor", "middle")
    .text("Carmine")
    .append("tspan")
    .attr("x", 3*width/8 )
    .attr("y", height/4-55)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .text("Osvaldo");

svg.append("line")
    .attr("x1",2*width/8+50)
    .attr("y1",height/4-48)
    .attr("x2",3*width/8)
    .attr("y2",height/4-48);


// Create Line Henk_Bodrogi to Carmine_Osvaldo
svg.append("line")
    .attr("x1",2*width/8+50)
    .attr("y1",height/4+5)
    .attr("x2",3*width/8)
    .attr("y2",height/4+5);

//Create Jeroen Karel
var Jeroen_Karel = svg
    .append("rect")
    .attr("x", 3*width/8)
    .attr("y", height/4-20)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10);

svg.append("text")
    .attr("x", 3*width/8 )
    .attr("y", height/4-20)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .style("text-anchor", "middle")
    .text("Jeroen")
    .append("tspan")
    .attr("x", 3*width/8 )
    .attr("y", height/4-5)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .text("Karel");

//Create Valentine
var Valentine_Mies = svg
    .append("rect")
    .attr("x", 3*width/8)
    .attr("y", height/4+30)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10);

svg.append("text")
    .attr("x", 3*width/8 )
    .attr("y", height/4+30)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .style("text-anchor", "middle")
    .text("Valentine")
    .append("tspan")
    .attr("x", 3*width/8 )
    .attr("y", height/4+45)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .text("Mies");

// Create Line Valentine Mies
svg.append("line")
    .attr("x1",2*width/8+50)
    .attr("y1",height/4+55)
    .attr("x2",3*width/8)
    .attr("y2",height/4+55);

//Create Ale_Hanne
var Ale_Hanne = svg
    .append("rect")
    .attr("x", 3*width/8)
    .attr("y", height/4+80)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10);

svg.append("text")
    .attr("x", 3*width/8 )
    .attr("y", height/4+80)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .style("text-anchor", "middle")
    .text("Ale")
    .append("tspan")
    .attr("x", 3*width/8 )
    .attr("y", height/4+95)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .text("Hann");

// Create Line Valentine Mies to Ale_Hanne
svg.append("line")
    .attr("x1",2*width/8+50)
    .attr("y1",height/4+105)
    .attr("x2",3*width/8)
    .attr("y2",height/4+105);

//Create Joreto_Katell
var Joreto_Katell = svg
    .append("rect")
    .attr("x", 3*width/8)
    .attr("y", height/4+130)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10);

svg.append("text")
    .attr("x", 3*width/8 )
    .attr("y", height/4+130)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .style("text-anchor", "middle")
    .text("Joreto")
    .append("tspan")
    .attr("x", 3*width/8 )
    .attr("y", height/4+145)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .text("Katell");

// Create Line Joreto_Katell
svg.append("line")
    .attr("x1",2*width/8+50)
    .attr("y1",height/4+155)
    .attr("x2",3*width/8)
    .attr("y2",height/4+155);

//Create Yanick_Cato
var Yanick_Cato = svg
    .append("rect")
    .attr("x", 3*width/8)
    .attr("y", height/4+180)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10);

svg.append("text")
    .attr("x", 3*width/8 )
    .attr("y", height/4+180)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .style("text-anchor", "middle")
    .text("Yanick")
    .append("tspan")
    .attr("x", 3*width/8 )
    .attr("y", height/4+195)
    .attr("dy", "20px")
    .attr("dx", "45px")
    .text("Cato");

// Create Line Yanick_Cato 
svg.append("line")
    .attr("x1",2*width/8+50)
    .attr("y1",height/4+205)
    .attr("x2",3*width/8)
    .attr("y2",height/4+205);


//Create Elain_Karel
var Elain_Karel = svg
    .append("rect")
    .attr("class", "bold")
    .attr("x", 1*width/8)
    .attr("y", 2*height/4+50)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10);

svg.append("text")
    .attr("x", 1*width/8 )
    .attr("y", 2*height/4+50)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .style("text-anchor", "middle")
    .text("Elain")
    .append("tspan")
    .attr("x", 1*width/8 )
    .attr("y", 2*height/4+65)
    .attr("dy", "20px")
    .attr("dx", "50px")
    .text("Karel");


// Create Line Henk Bodrogi to Elain_Karel
svg.append("line")
    .attr("x1",1*width/8+50)
    .attr("y1",2*height/4+5)
    .attr("x2",1*width/8+50)
    .attr("y2",2*height/4+50)
    .attr("marker-end","url(#markerEnd)");

//Create Silvia_Marek and Mandor_Vann
var Silvia_Marek = svg
    .append("rect")
    .attr("x", 1*width/8-55)
    .attr("y", 3*height/4+50)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10)
    .style("visibility", "hidden");

var Mandor_Vann = svg
    .append("rect")
    .attr("x", 1*width/8+55)
    .attr("y", 3*height/4+50)
    .attr("width", 100)
    .attr("height", 45)
    .attr("rx", 10)
    .attr("ry", 10)
    .style("visibility", "hidden");

// Create text

var textplace= svg
    .append("rect")
    //.style("stroke", "none");
    .style("stroke", "#514C55")
    .style("stroke-width", "5");

textplace
    .attr("x", 4*width/8+80)
    .attr("y", (1*height/4)-50)
    .attr("width", 5*width/8)
    .attr("height", height/4+245)
    .attr("rx", 10)
    .attr("ry", 10)
    .style("visibility", "hidden");


var texttitle = svg.append("foreignObject")
    .attr("x", 4*width/8+95)
    .attr("y", (1*height/4)-40)
    .attr("width", 5*width/8-10)
    .attr("height", height/4+230)
    ;

// Add Data
Henk_Bodrogi.on("click", function() {
    Carmine_Osvaldo.transition()
        .style("fill", "#6699FF");
    Jeroen_Karel.transition()
        .style("fill", "#6699FF");
    Elain_Karel.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#6699FF");
    Henk_Bodrogi.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    texttitle.text("The grassroots organization coalesced under the leadership of Henk Bodrogi, a floodplain farmer who had joined the group after his wife had become ill with cardiopulmonary symptoms consistent with ethylene glycol contamination.  Bodrogi was a popular local figure who was well regarded for his leadership in civic groups.  Although he had served in the Kronosian military, Bodrogi lacked experience in dealing with the Kronosian government and for which he turned to his lifelong friend, Carmine Osvaldo. Osvaldo, who had served in the military with Bodrogi, was a member of the board for the Elodis Chamber of Commerce and who used his business experience to form relationships with the Kronosian government and outside agencies.").style("color", "white");
    svg.selectAll(".invisible").data([]).exit().remove();
    Silvia_Marek.style("visibility", "hidden");
    Mandor_Vann.style("visibility", "hidden");
    d3.event.stopPropagation();
});

Carmine_Osvaldo.on("click", function() {
    Henk_Bodrogi.transition()
        .style("fill", "#6699FF");
    Jeroen_Karel.transition()
        .style("fill", "#6699FF");
    Elain_Karel.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#6699FF");
    Carmine_Osvaldo.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    texttitle.style("color","white").text(" Osvaldo, who had served in the military with Bodrogi, was a member of the board for the Elodis Chamber of Commerce and who used his business experience to form relationships with the Kronosian government and outside agencies.Osvaldo proposed to the activists that they form a social movement organization with an identity brand and a specific agenda as a mechanism for interfacing with the government of Kronos.  The group chose the name “Protectors of Kronos” and developed a logo consisting of an open right hand rising from the land on a black background.  Additionally, Osvaldo contacted Wellness for All (WFA), an international agency that specialized in providing clean water for rural communities. ");
    svg.selectAll(".invisible").data([]).exit().remove();
    Silvia_Marek.style("visibility", "hidden");
    Mandor_Vann.style("visibility", "hidden");
    d3.event.stopPropagation();
});

Elain_Karel.on("click", function() {
    Henk_Bodrogi.transition()
        .style("fill", "#6699FF");
    Jeroen_Karel.transition()
        .style("fill", "#6699FF");
    Carmine_Osvaldo.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#6699FF");
    Silvia_Marek.transition()
        .style("fill", "red");
    Elain_Karel.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    texttitle.style("color", "white").text("Current leader of the POK, Karel is a dynamic speaker whose charismatic leadership abilities have won him a substantial group of loyal supporters.  The POK continues to grow in size under Karel’s leadership.  His growing popularity with the citizens of Kronos and certain media organizations is likely to gain interest in the POK agenda among General Assembly members.");
    svg.selectAll(".invisible").data([]).exit().remove();

    Silvia_Marek.transition()
        .style("visibility", "visible");

    Mandor_Vann.transition()
        .style("visibility", "visible");

    svg.append("line")
        .attr("class", "invisible futureleadership")
        .attr("x1", 1*width/8-50 )
        .attr("y1", 3*height/4+10)
        .attr("x2", 1*width/8+150 )
        .attr("y2", 3*height/4+10);

    svg.append("text")
        .attr("class", "invisible futureleadership")
        .style("stroke", "none")
        .attr("x", 1*width/8-50 )
        .attr("y", 3*height/4+10)
        .attr("dy", "20px")
        .attr("dx", "20px")
        .text("Future Leaders of POK");

    svg.append("text")
        .attr("class", "invisible")
        .attr("x", 1*width/8-55 )
        .attr("y", 3*height/4+50)
        .attr("dy", "20px")
        .attr("dx", "50px")
        .style("text-anchor", "middle")
        .text("Silvia")
        .append("tspan")
        .attr("x", 1*width/8 -55)
        .attr("y", 3*height/4+65)
        .attr("dy", "20px")
        .attr("dx", "50px")
        .text("Marek");

    svg.append("g")
        .append("path")
        .attr("class", "link invisible")
        .attr("stroke-dasharray", "10,10")
        .attr("marker-end","url(#markerEnd)")
        .attr("d", function() {
            var dx = (1*width/8+50) - (1*width/8-10),
                dy =  (3*height/4-5)- (4*height/4-50),
                dr = Math.sqrt(dx * dx + dy * dy);
            return "M" +
                (1*width/8+50) + "," +
                (3*height/4-5)+
                "A" +
                dr + "," + dr + " 0 0,1 " +
                (1*width/8-10) + "," +
                (4*height/4-50)
                ;
        });

    svg.append("text")
        .attr("class", "invisible")
        .attr("x", 1*width/8+55 )
        .attr("y", 3*height/4+50)
        .attr("dy", "20px")
        .attr("dx", "50px")
        .style("text-anchor", "middle")
        .text("Mandor")
        .append("tspan")
        .attr("x", 1*width/8+55 )
        .attr("y", 3*height/4+65)
        .attr("dy", "20px")
        .attr("dx", "50px")
        .text("Vann");

    svg.append("g")
        .append("path")
        .attr("class", "link invisible")
        .attr("marker-start","url(#markerStart)")
        .attr("stroke-dasharray", "10,10")
        .attr("d", function() {
            var dx = (1*width/8+50) - (2*width/8-10),
                dy =  (2*height/4+95)- (3*height/4+50),
                dr = Math.sqrt(dx * dx + dy * dy);
            return "M" +
                (2*width/8-10)+ "," +
                (3*height/4+50)+
                "A" +
                dr + "," + dr + " 0 0,1 " +
                (1*width/8+50) + "," +
                (2*height/4+95)
                ;
        });


    d3.event.stopPropagation();
});

Jeroen_Karel.on("click", function() {
    Henk_Bodrogi.transition()
        .style("fill", "#6699FF");
    Elain_Karel.transition()
        .style("fill", "#6699FF");
    Carmine_Osvaldo.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#6699FF");
    Jeroen_Karel.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    texttitle.style("color","white").text("Jeroen Karel, father of current POK leader Elian Karel, to organize recruitment and personnel. ");
    svg.selectAll(".invisible").data([]).exit().remove();
    Silvia_Marek.style("visibility", "hidden");
    Mandor_Vann.style("visibility", "hidden");
    d3.event.stopPropagation();
});

Mandor_Vann.on("click", function() {
    Henk_Bodrogi.transition()
        .style("fill", "#6699FF");
    Elain_Karel.transition()
        .style("fill", "#6699FF");
    Carmine_Osvaldo.transition()
        .style("fill", "#6699FF");
    Silvia_Marek.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#6699FF");
    Mandor_Vann.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    texttitle.style("color", "white").text("Mandor Vann, uncle to Isia and Juliana Vann, has been with the POK since retiring from the Kronos military in 2004.  Vann, who was an enlisted linguist, spent much of his military career serving at the Kronosian embassies in Tethys and Asteria.  As the POK member with the most experience in government, Vann has become the group’s top political strategist.  POK members have great respect for Vann and describe him as intense, intelligent, organized, and ambitious.");
    d3.event.stopPropagation();
});

Silvia_Marek.on("click", function() {
    Henk_Bodrogi.transition()
        .style("fill", "#6699FF");
    Elain_Karel.transition()
        .style("fill", "#6699FF");
    Carmine_Osvaldo.transition()
        .style("fill", "#6699FF");
    Mandor_Vann.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#6699FF");
    Silvia_Marek.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    texttitle.html('<div class="text" style="width: '+(7*width/8-10)+'px;  color:#ECE9E0; font: 12px sans-serif;">'
                     +'<h3>Silvia Marek</h3>'
                       +'<h4>*Leader and co-founder of Save Our Wildlands (U of Abila).</h4>' 
                         +'<h4>*Passion for vegan lifestyle and environmental awareness.</h4>' 
                           +'<h4>After Henk Bodrogi stepped down as leader of the POK, Mies followed him.</h4>'
                             +'</div>');

    d3.event.stopPropagation();
});

Valentine_Mies.on("click", function() {
    Henk_Bodrogi.transition()
        .style("fill", "#6699FF");
    Elain_Karel.transition()
        .style("fill", "#6699FF");
    Carmine_Osvaldo.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    texttitle.html('<div class="text" style="width: '+(7*width/8-10)+'px;  color:#ECE9E0; font: 12px sans-serif;">' + '<h3>Valentine Mies</h3><h4> Citizen of Eladis</h4> <h4> One of the seven founding members of the Protectors of Kronos</h4><h4>After Henk Bodrogi stepped down as leader of the POK, Mies followed him.</h4>'+'</div>');
    texttitle.style("color", "white");
    svg.selectAll(".invisible").data([]).exit().remove();
    Silvia_Marek.style("visibility", "hidden");
    Mandor_Vann.style("visibility", "hidden");
    d3.event.stopPropagation();
});

Ale_Hanne.on("click", function() {
    Henk_Bodrogi.transition()
        .style("fill", "#6699FF");
    Elain_Karel.transition()
        .style("fill", "#6699FF");
    Carmine_Osvaldo.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    texttitle.html('<div class="text" style="width: '+(7*width/8-10)+'px;  color:#ECE9E0; font: 12px sans-serif;">' + '<h3>Ale Hanne</h3><h4> Citizen of Eladis</h4> <h4> One of the seven founding members of the Protectors of Kronos</h4><h4>After Henk Bodrogi stepped down as leader of the POK, Hanne followed him.</h4>'+'</div>');
    svg.selectAll(".invisible").data([]).exit().remove();
    Silvia_Marek.style("visibility", "hidden");
    Mandor_Vann.style("visibility", "hidden");
    d3.event.stopPropagation();
});

Joreto_Katell.on("click", function() {
    Henk_Bodrogi.transition()
        .style("fill", "#6699FF");
    Elain_Karel.transition()
        .style("fill", "#6699FF");
    Carmine_Osvaldo.transition()
        .style("fill", "#6699FF");
    Jeroen_Karel.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    d3.text("katell.html", function(unparsedData){
        texttitle.html('<div class="text" style="width: '+(7*width/8-10)+'px;  color:#ECE9E0; font: 12px sans-serif;">' +
            unparsedData+ '</div>')
    });
    svg.selectAll(".invisible").data([]).exit().remove();
    Silvia_Marek.style("visibility", "hidden");
    Mandor_Vann.style("visibility", "hidden");
    d3.event.stopPropagation();
});

Yanick_Cato.on("click", function() {
    Henk_Bodrogi.transition()
        .style("fill", "#6699FF");
    Elain_Karel.transition()
        .style("fill", "#6699FF");
    Carmine_Osvaldo.transition()
        .style("fill", "#6699FF");
    Jeroen_Karel.transition()
        .style("fill", "#6699FF");
    Valentine_Mies.transition()
        .style("fill", "#6699FF");
    Ale_Hanne.transition()
        .style("fill", "#6699FF");
    Joreto_Katell.transition()
        .style("fill", "#6699FF");
    Yanick_Cato.transition()
        .style("fill", "#003366");

    textplace.style("visibility", "visible");
    textplace.transition().style("fill", "#003366");
    d3.text("cato.html", function(unparsedData){
        texttitle.html('<div class="text" style="width: '+(7*width/8-10)+'px;  color:#ECE9E0; font: 12px sans-serif;">' +
            unparsedData+ '</div>')
    });
    svg.selectAll(".invisible").data([]).exit().remove();
    Silvia_Marek.style("visibility", "hidden");
    Mandor_Vann.style("visibility", "hidden");
    d3.event.stopPropagation();
});