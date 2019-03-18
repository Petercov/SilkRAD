#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <bitset>
#include <memory>

#include <cstdlib>
#include <cassert>

#include "bsp.h"


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Invalid arguments." << std::endl;
        return 1;
    }
    
    const std::string filename(argv[1]);
    std::ifstream f(filename, std::ios::binary);
    
    std::unique_ptr<BSP::BSP> pBSP;
    
    try {
        pBSP = std::unique_ptr<BSP::BSP>(new BSP::BSP(filename));
    }
    catch (BSP::InvalidBSP e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "BSP Version " << pBSP->get_format_version() << std::endl;
    std::cout << "Fullbright: " << pBSP->is_fullbright() << std::endl;
    
    const std::vector<BSP::DLeafAmbientLighting>& ambientLighting =
        pBSP->get_ambient_samples();
    
    int leafIndex = 0;
    for (const BSP::DLeafAmbientIndex& index : pBSP->get_ambient_indices()) {
        std::cout << "Leaf " << leafIndex
            << " (" << index.ambientSampleCount << " ambient samples):"
            << std::endl;
            
        int start = index.firstAmbientSample;
        int stop = start + index.ambientSampleCount;
        
        for (int i=start; i<stop; i++) {
            const BSP::DLeafAmbientLighting& sample = ambientLighting[i];
            std::cout << "    Sample " << i - start << " @ ("
                << static_cast<int>(sample.x) << ", "
                << static_cast<int>(sample.y) << ", "
                << static_cast<int>(sample.z) << "): " << std::endl;
            
            std::vector<std::string> dirLabels {
                "+X", "-X",
                "+Y", "-Y",
                "+Z", "-Z",
            };
            
            for (int dir=0; dir<6; dir++) {
                std::cout << "        " << dirLabels[dir] << ": ("
                    << static_cast<int>(sample.cube.color[dir].r) << ", "
                    << static_cast<int>(sample.cube.color[dir].g) << ", "
                    << static_cast<int>(sample.cube.color[dir].b) << ") * 2^"
                    << static_cast<int>(sample.cube.color[dir].exp)
                    << std::endl;
            }
        }
        
        leafIndex++;
    }
    
    // int i = 0;
    // for (BSP::Face& face : pBSP->get_faces()) {
        // std::cout << "Face " << i << ":" << std::endl;
        
        // for (const BSP::Edge& edge : face.get_edges()) {
            // const BSP::Vec3<float>& vertex1 = edge.vertex1;
            // const BSP::Vec3<float>& vertex2 = edge.vertex2;
            
            // std::cout << "    ("
                // << vertex1.x << ", "
                // << vertex1.y << ", "
                // << vertex1.z << ") -> ("
                // << vertex2.x << ", "
                // << vertex2.y << ", "
                // << vertex2.z << ")"
                // << std::endl;
        // }
        
        // std::cout <<  "    Styles:" << std::endl;
        
        // int j = 0;
        // for (uint8_t style : face.get_styles()) {
            // std::cout << "        " << j << " "
                // << std::bitset<sizeof(style) * 8>(style)
                // << std::endl;
            // j++;
        // }
        
        // const BSP::DFace& faceData = face.get_data();
        
        // std::cout << "    Light Offset: "
            // << faceData.lightOffset / sizeof(BSP::RGBExp32) << std::endl;
        
        // std::cout << "    Luxels X: "
            // << face.get_lightmap_width()
            // << std::endl
            // << "    Luxels Y: "
            // << face.get_lightmap_height()
            // << std::endl;
            
        // std::cout << "    "
            // << face.get_lightmap_size() << " Light Samples" << std::endl;
            
        // const BSP::RGBExp32& avgLighting = face.get_average_lighting();
        
        // std::cout << "    Average Lighting: ("
            // << static_cast<int>(avgLighting.r) << ", "
            // << static_cast<int>(avgLighting.g) << ", "
            // << static_cast<int>(avgLighting.b) << ") * 2^"
            // << static_cast<int>(avgLighting.exp) << std::endl;
            
        // // std::cout << "    Light Samples:" << std::endl;
        
        // // j = 0;
        // // for (BSP::RGBExp32& lightSample : face.get_lightsamples()) {
            // // std::cout << "        Sample " << j << ": ("
                // // << static_cast<int>(lightSample.r) << ", "
                // // << static_cast<int>(lightSample.g) << ", "
                // // << static_cast<int>(lightSample.b) << ") * 2^"
                // // << static_cast<int>(lightSample.exp) << std::endl;
            // // j++;
        // // }
        
        // // std::cout << "    Light Sample Coords:" << std::endl;
        
        // // for (size_t i=0; i<face.get_lightmap_size(); i++) {
            // // double s = static_cast<double>(i % face.get_lightmap_width());
            // // double t = static_cast<double>(i / face.get_lightmap_width());
            
            // // BSP::Vec3<float> pos = face.xyz_from_lightmap_st(s, t);
            
            // // std::cout << "        Sample " << i << ": <"
                // // << pos.x << ", "
                // // << pos.y << ", "
                // // << pos.z << ">" << std::endl;
        // // }
        
        // const BSP::TexInfo& texInfo = face.get_texinfo();
        // const BSP::DTexData& texData = face.get_texdata();
        // const BSP::DPlane& planeData = face.get_planedata();
        
        // std::cout << "    Texinfo Index: " << faceData.texInfo << std::endl;
        
        // std::cout << "    Plane Number: " << faceData.planeNum << std::endl;
        
        // std::cout << "    Face Normal: <"
            // << planeData.normal.x << ", "
            // << planeData.normal.y << ", "
            // << planeData.normal.z << ">"
            // << std::endl;
            
        // std::cout << "    Plane Distance: " << planeData.dist << std::endl;
        
        // std::cout << "    Lightmap Mins: "
            // << faceData.lightmapTextureMinsInLuxels[0] << ", "
            // << faceData.lightmapTextureMinsInLuxels[1] << std::endl;
            
        // std::cout << "    Lightmap S vector: <"
            // << texInfo.lightmapVecs[0][0] << ", "
            // << texInfo.lightmapVecs[0][1] << ", "
            // << texInfo.lightmapVecs[0][2] << ", "
            // << texInfo.lightmapVecs[0][3] << ">"
            // << std::endl;
            
        // std::cout << "    Lightmap T vector: <"
            // << texInfo.lightmapVecs[1][0] << ", "
            // << texInfo.lightmapVecs[1][1] << ", "
            // << texInfo.lightmapVecs[1][2] << ", "
            // << texInfo.lightmapVecs[1][3] << ">"
            // << std::endl;
            
        // /**/
        
        // BSP::Vec3<float> cross {
            // texInfo.lightmapVecs[1][1] * texInfo.lightmapVecs[0][2] - texInfo.lightmapVecs[1][2] * texInfo.lightmapVecs[0][1],
            // texInfo.lightmapVecs[1][2] * texInfo.lightmapVecs[0][0] - texInfo.lightmapVecs[1][0] * texInfo.lightmapVecs[0][2],
            // texInfo.lightmapVecs[1][0] * texInfo.lightmapVecs[0][1] - texInfo.lightmapVecs[1][1] * texInfo.lightmapVecs[0][0],
        // };
        
        // std::cout << "    ST Cross: <"
            // << cross.x << ", "
            // << cross.y << ", "
            // << cross.z << ">" << std::endl;
            
        // float det = -(
            // planeData.normal.x * cross.x +
            // planeData.normal.y * cross.y +
            // planeData.normal.z * cross.z
        // );
        
        // std::cout << "    ST Determinant: " << det << std::endl;
        
        // assert(((det < 0) ? -det : det) >= 1e-20);
        
        // BSP::Vec3<float> invS {
            // (planeData.normal.z * texInfo.lightmapVecs[1][1] - planeData.normal.y * texInfo.lightmapVecs[1][2]) / det,
            // (planeData.normal.x * texInfo.lightmapVecs[1][2] - planeData.normal.z * texInfo.lightmapVecs[1][0]) / det,
            // (planeData.normal.y * texInfo.lightmapVecs[1][0] - planeData.normal.x * texInfo.lightmapVecs[1][1]) / det,
        // };
        
        // BSP::Vec3<float> invT {
            // (planeData.normal.y * texInfo.lightmapVecs[0][2] - planeData.normal.z * texInfo.lightmapVecs[0][1]) / det,
            // (planeData.normal.z * texInfo.lightmapVecs[0][0] - planeData.normal.x * texInfo.lightmapVecs[0][2]) / det,
            // (planeData.normal.x * texInfo.lightmapVecs[0][1] - planeData.normal.y * texInfo.lightmapVecs[1][1]) / det,
        // };
        
        // BSP::Vec3<float> luxelOrigin {
            // -(planeData.dist * cross.x) / det,
            // -(planeData.dist * cross.y) / det,
            // -(planeData.dist * cross.z) / det,
        // };
        
        // luxelOrigin.x = luxelOrigin.x + texInfo.lightmapVecs[0][3] * invS.x;
        // luxelOrigin.y = luxelOrigin.y + texInfo.lightmapVecs[0][3] * invS.y;
        // luxelOrigin.z = luxelOrigin.z + texInfo.lightmapVecs[0][3] * invS.z;
        
        // luxelOrigin.x = luxelOrigin.x + texInfo.lightmapVecs[1][3] * invT.x;
        // luxelOrigin.y = luxelOrigin.y + texInfo.lightmapVecs[1][3] * invT.y;
        // luxelOrigin.z = luxelOrigin.z + texInfo.lightmapVecs[1][3] * invT.z;
        
        // std::cout << "    Inverted S: <"
            // << invS.x << ", "
            // << invS.y << ", "
            // << invS.z << ">" << std::endl;
            
        // std::cout << "    Inverted T: <"
            // << invT.x << ", "
            // << invT.y << ", "
            // << invT.z << ">" << std::endl;
            
        // std::cout << "    Luxel Origin: <"
            // << luxelOrigin.x << ", "
            // << luxelOrigin.y << ", "
            // << luxelOrigin.z << ">" << std::endl;
            
        // /**/
        
        // std::cout << "    Texture Width: " << texData.width << std::endl;
        // std::cout << "    Texture Height: " << texData.height << std::endl;
        
        // i++;
    // }
    
    // int i = 0;
    // for (const BSP::Light& light : pBSP->get_lights()) {
        // std::cout << "Light " << i << ":" << std::endl;
        
        // const BSP::Vec3<float>& pos = light.get_coords();
        // std::cout << "    pos: ("
            // << pos.x << ", "
            // << pos.y << ", "
            // << pos.z << ")" << std::endl;
            
        // std::cout << "    r: " << light.r << std::endl;
        // std::cout << "    g: " << light.g << std::endl;
        // std::cout << "    b: " << light.b << std::endl;
        
        // std::cout << "    Direction: <"
            // << light.direction.x << ", "
            // << light.direction.y << ", "
            // << light.direction.z << ">" << std::endl;
        
        // std::cout << "    Outer Cone: " << light.outerCone << std::endl;
        // std::cout << "    Inner Cone: " << light.innerCone << std::endl;
        
        // i++;
    // }
    
    // // std::cout << "Ent Data: " << std::endl;
    // // std::cout << pBSP->get_entdata() << std::endl;
    
    // pBSP->build_worldlights();
    
    // std::cout << "World Lights: " << std::endl;
    
    // i = 0;
    // for (const BSP::DWorldLight& worldLight : pBSP->get_worldlights()) {
        // std::cout << "    World Light " << i << ":" << std::endl;
        
        // std::cout << "        origin: ("
            // << worldLight.origin.x << ", "
            // << worldLight.origin.y << ", "
            // << worldLight.origin.z << ")" << std::endl;
            
        // std::cout << "        intensity: ("
            // << worldLight.intensity.x << ", "
            // << worldLight.intensity.y << ", "
            // << worldLight.intensity.z << ")" << std::endl;
            
        // std::cout << "        normal: <"
            // << worldLight.normal.x << ", "
            // << worldLight.normal.y << ", "
            // << worldLight.normal.z << ">" << std::endl;
            
        // std::cout << "        cluster: " << worldLight.cluster << std::endl;
        // std::cout << "        type: " << worldLight.type << std::endl;
        // std::cout << "        style: " << worldLight.style << std::endl;
        // std::cout << "        stopdot: " << worldLight.stopdot << std::endl;
        // std::cout << "        stopdot2: " << worldLight.stopdot2 << std::endl;
        // std::cout << "        exponent: " << worldLight.exponent << std::endl;
        // std::cout << "        radius: " << worldLight.radius << std::endl;
        // std::cout << "        const: " << worldLight.constantAtten << std::endl;
        // std::cout << "        lin: " << worldLight.linearAtten << std::endl;
        // std::cout << "        quad: " << worldLight.quadraticAtten << std::endl;
        // std::cout << "        flags: " << worldLight.flags << std::endl;
        // std::cout << "        texinfo: " << worldLight.texinfo << std::endl;
        // std::cout << "        owner: " << worldLight.owner << std::endl;
        
        // i++;
    // }
    
    // std::cout << "Entities:" << std::endl;
    // std::cout << pBSP->get_entdata() << std::endl;
    
    pBSP->write("out.bsp");
    
    return 0;
}
